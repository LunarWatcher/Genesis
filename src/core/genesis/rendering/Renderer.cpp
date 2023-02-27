#include "Renderer.hpp"

#include "GLFW/glfw3.h"

#include "genesis/rendering/Shader.hpp"
#include "genesis/core/game/World.hpp"
#include "genesis/core/game/generation/WorldGenerator.hpp"
#include "genesis/rendering/Texture.hpp"
#include "genesis/rendering/atlases/FontAtlas.hpp"
#include "shaders/DefaultShader.hpp"
#include "genesis/conf/Settings.hpp"

#include "genesis/core/menu/Menu.hpp"

#include <chrono>
#include <codecvt>
#include <iostream>
#include <locale>
#include <thread>

namespace genesis {

Renderer::Renderer() {
    INSTANCE = this;

    glfwSetErrorCallback(GLFWDebug::GLFWCallback);

    glewExperimental = true;
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_RESIZABLE, false);
#if defined __APPLE__ || defined __OSX__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);


    this->window = glfwCreateWindow(Settings::instance->getInt("width"),
        Settings::instance->getInt("height"),
        "Genesis",
        nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to open GLFW window");
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize glew");
    }

    glfwSwapInterval(1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_MULTISAMPLE);

    glEnable(GL_LINE_SMOOTH);

#ifdef API_DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
#endif

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    initGame();
    initFonts();

    auto menu = std::make_shared<MenuScene>();

    transition(menu);
    logger->info("Initialized menu");
}

void Renderer::initGame() {
    using namespace std::placeholders;

    this->camera = std::make_shared<Camera>();

    this->texturePack = std::make_shared<genesis::TextureAtlas>("images/programmer.png");

    this->textureShader = std::make_shared<DefaultShader>();
    this->primitiveShader = std::make_shared<DefaultShader>("primitive");
    this->textShader = std::make_shared<TextShader>();

    glfwSetWindowUserPointer(window, this);
    // Input
    glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int, int action, int mods) {
        if (action == GLFW_REPEAT) return;
        Renderer* r = (Renderer*) glfwGetWindowUserPointer(win);
        r->keyStates[InputProcessor::createMapKey(key, mods)] = action;
    });
    glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int mods) {
        if (action == GLFW_REPEAT) return;
        Renderer* r = (Renderer*) glfwGetWindowUserPointer(win);

        r->keyStates[InputProcessor::createMapKey(button, mods)] = action;
    });
    glfwSetCursorPosCallback(window, [](GLFWwindow* win, double x, double y) {
        Renderer* r = (Renderer*) glfwGetWindowUserPointer(win);
        for (auto& scene : r->activeSceneStack) {
            if (scene->onMouseMoved(x, y)) {
                break;
            }
        }
    });
}

void Renderer::initFonts() {
    //if (FT_Init_FreeType(&this->fontLibrary)) {
        //std::cerr << "Failed to initialize freetype" << std::endl;
        //throw std::runtime_error("Freetype died");
    //}
    this->fontAtlas = std::make_shared<FontAtlas>();

}

void Renderer::tick() {
    for (auto& scene : activeSceneStack) {
        scene->updateInput(keyStates);
        scene->tick();
    }

    for (auto& [k, v] : keyStates) {
        if (v == GLFW_RELEASE) {
            v = -1;
        }
    }
}

void Renderer::render() {
    camera->regenerateCameraMatrix();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.529, 0.8078, 0.922, 1);

    // TODO: set up a system to allow scenes to define these.
    // Though I'm not entirely sure if that's even necessary.
    // A few bits are tied to the camera class, but I'm not
    // sure if that's used elsewhere.
    // if it is, we may need to hook up a system that exposes
    // the currently rendered scene in a pointer or something.
    // It's already a pointer, so it's a fairly cheap operation.
    //
    // Just use some common sense though.
    // Update shader data {{{
    textureShader->apply();
    textureShader->loadViewMatrix(camera->getViewMatrix());
    // we don't need to call stop for each shader.
    // Apply overwrites any other enabled shaders.
    // I think.
    // At least for a single type.
    textShader->stop();
    // }}}

    for (auto& scene : activeSceneStack) {
        if (scene == nullptr) {
            logger->error("Expected scene to be non-null, but got null");
            throw std::runtime_error("Received null scene during rendering");
        }
        // TODO: respect paused behavior
        scene->render();
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Renderer::run() {
    auto targetTime = std::chrono::duration<double, std::milli>(8.3);

    auto lastTime = std::chrono::high_resolution_clock::now();
    auto counter = lastTime;
    int frames = 0;
    do {
        auto now = std::chrono::high_resolution_clock::now();
        delta = std::chrono::duration<double, std::ratio<1>>(now - lastTime).count();

        tick();
        render();

        auto end = std::chrono::high_resolution_clock::now();
        lastTime = end;
        auto sleepFor = targetTime - (now - end);
        if (sleepFor > std::chrono::milliseconds(0)) {
            std::this_thread::sleep_for(sleepFor);
        }
        ++frames;
        if (std::chrono::high_resolution_clock::now() - counter > std::chrono::seconds(1)) {
            counter = std::chrono::high_resolution_clock::now();
            frames = 0;
        }
    } while (glfwWindowShouldClose(window) == 0);

    glfwTerminate();
}

// Scene management {{{
void Renderer::transition(const std::shared_ptr<Scene>& scene) {
    for (auto& stg : activeSceneStack) {
        stg->onDestroy();
    }
    activeSceneStack.clear();
    activeSceneStack.push_back(scene);

}

void Renderer::add(const std::shared_ptr<Scene>& scene) {
    activeSceneStack.push_back(scene);
}

void Renderer::pop(const std::shared_ptr<Scene>& scene) {
    if (auto sc = std::find(activeSceneStack.begin(), activeSceneStack.end(), scene);
            sc != activeSceneStack.end()) {
        activeSceneStack.erase(sc);
        return;
    }
    throw std::runtime_error("Tried to pop a non-existent item");
}

void Renderer::createGame() {
    logger->info("Creating game.");
    WorldGenerator::newWorld(3, 3, "The Great Roman Empire");
}

// }}}

void Renderer::refreshDisplay() {
    bool fullscreen = Settings::instance->getBool("fullscreen");

    // TODO: toggle fullscreen
}

} // namespace genesis