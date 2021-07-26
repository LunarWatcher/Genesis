#include "Renderer.hpp"

#include "GLFW/glfw3.h"

#include "Shader.hpp"
#include "genesis/core/WorldController.hpp"
#include "genesis/rendering/Texture.hpp"
#include "genesis/rendering/atlases/FontAtlas.hpp"
#include "shaders/DefaultShader.hpp"

#include <chrono>
#include <codecvt>
#include <iostream>
#include <locale>
#include <thread>

namespace genesis {

Renderer::Renderer() {
    INSTANCE = this;

    glewExperimental = true;
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE, false);
#if defined __APPLE__ || defined __OSX__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    glfwSwapInterval(1);

    this->window = glfwCreateWindow(1024, 576, "Genesis", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to open GLFW window");
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize glew");
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_MULTISAMPLE);

#ifdef API_DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
#endif

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initGame();
    initFonts();
}

void Renderer::initGame() {
    this->inputManager = std::make_shared<InputManager>();
    this->camera = std::make_shared<Camera>();

    this->texturePack = std::make_shared<genesis::WorldTexture>("images/programmer.png");

    this->physicsController = std::make_shared<PhysicsWorld>();

    auto wc = std::make_shared<WorldController>();
    transition(wc);

    wc->generate();

    this->textureShader = std::make_shared<DefaultShader>();
    this->textShader = std::make_shared<TextShader>();
    this->particleShader = std::make_shared<ParticleShader>();

    this->textShader->apply();
    this->textShader->loadTextColor({0, 0, 0, 1.0});
    this->textShader->stop();

    // Input
    glfwSetWindowUserPointer(window, inputManager.get());
    glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scanCode, int action, int mods) {
        ((InputManager*) glfwGetWindowUserPointer(win))->onKeyPressed(key, scanCode, action, mods);
    });
    glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int mods) {
        ((InputManager*) glfwGetWindowUserPointer(win))->onMousePressed(button, action, mods);
    });
    glfwSetCursorPosCallback(window, [](GLFWwindow* win, double x, double y) {
        ((InputManager*) glfwGetWindowUserPointer(win))->onMouseMoved(x, y);
    });
}

void Renderer::initFonts() {
    if (FT_Init_FreeType(&this->fontLibrary)) {
        std::cerr << "Failed to initialize freetype" << std::endl;
        throw std::runtime_error("Freetype died");
    }
    this->fontAtlas = std::make_shared<FontAtlas>();

}

void Renderer::tick() {
    for (auto scene : activeSceneStack) {
        scene->tick();
    }
}

void Renderer::render() {
    camera->regenerateCameraMatrix();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.529, 0.8078, 0.922, 1);

    // Update shader data {{{
    textureShader->apply();
    textureShader->loadViewMatrix(camera->getViewMatrix());
    textureShader->stop();

    particleShader->apply();
    particleShader->loadViewMatrix(camera->getViewMatrix());
    particleShader->stop();
    // }}}
    for (auto scene : activeSceneStack) {
        // TODO: respect paused behavior
        scene->render();
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Renderer::run() {
    auto targetTime = std::chrono::duration<double, std::milli>(8.3);

    auto lastTime = std::chrono::high_resolution_clock::now();
    do {
        auto now = std::chrono::high_resolution_clock::now();
        delta = std::chrono::duration<double, std::ratio<1>>(now - lastTime).count();

        // TODO: figure out how to best design a loop that makes TPS \
        // and FPS separate (... at least partially)
        // At least to the point where FPS != TPS by loop definition
        // Though might never be a problem. A certain degree of async
        // processing might avoid that being necessesary.
        inputManager->tick();

        tick();
        render();

        auto end = std::chrono::high_resolution_clock::now();
        lastTime = end;
        auto sleepFor = targetTime - (now - end);
        if (sleepFor > std::chrono::milliseconds(0)) {
            std::this_thread::sleep_for(sleepFor);
        }
    } while (glfwWindowShouldClose(window) == 0);

    glfwTerminate();
}

// Scene management {{{
void Renderer::transition(std::shared_ptr<Scene> scene) {
    for (auto& stg : activeSceneStack) {
        stg->onDestroy();
    }
    activeSceneStack.clear();
    activeSceneStack.push_back(scene);
}

void Renderer::add(std::shared_ptr<Scene> scene) {
    activeSceneStack.push_back(scene);
}

void Renderer::pop(std::shared_ptr<Scene> scene) {
    if (auto sc = std::find(activeSceneStack.begin(), activeSceneStack.end(), scene);
            sc != activeSceneStack.end()) {
        activeSceneStack.erase(sc);
        return;
    }
    throw std::runtime_error("Tried to pop a non-existent item");
}

// }}}

} // namespace genesis
