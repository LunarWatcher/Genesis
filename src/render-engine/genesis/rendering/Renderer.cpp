#include "Renderer.hpp"

#include "GLFW/glfw3.h"

#include "genesis/conf/Settings.hpp"
#include "genesis/rendering/Shader.hpp"
#include "genesis/rendering/Texture.hpp"

#include <chrono>
#include <codecvt>
#include <iostream>
#include <locale>
#include <stdexcept>
#include <thread>

namespace genesis {

Renderer::Renderer() {
    glfwSetErrorCallback(GLFWDebug::GLFWCallback);

    glewExperimental = true;
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_RESIZABLE, false);
#if defined __APPLE__ || defined __OSX__
    // WTF is this for anyway? Does crapple really need to explicitly force 4.6?
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    this->window = glfwCreateWindow(
        Settings::instance->getInt("width"), Settings::instance->getInt("height"), "Genesis",
        nullptr, nullptr
    );

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
    // glEnable(GL_CULL_FACE);

    initGame();

    logger->info("Renderer initialised");
}

void Renderer::initGame() {
    // TODO: rename function
    using namespace std::placeholders;

    glfwSetWindowUserPointer(window, this);
    glfwSetCharCallback(window, [](GLFWwindow* /*win*/, unsigned int /*codepoint*/) {

    });
    // Input
    glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int, int action, int mods) {
        Renderer* r = (Renderer*) glfwGetWindowUserPointer(win);

        if (action == GLFW_REPEAT) {

            auto& keyState = r->keyStates[key];
            if (keyState.mods != mods) {
                keyState.mods = mods;
            }
            return;
        }

        r->keyStates[key] = {action, mods};
    });
    glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int mods) {
        Renderer* r = (Renderer*) glfwGetWindowUserPointer(win);

        if (action == GLFW_REPEAT) {
            auto& keyState = r->keyStates[button];
            if (keyState.mods != mods) {
                keyState.mods = mods;
            }
            return;
        }

        r->keyStates[button] = {action, mods};
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

void Renderer::tick() {
    for (auto& scene : activeSceneStack) {
        scene->updateInput(keyStates);
        scene->tick();
    }

    for (auto& [k, v] : keyStates) {
        if (v.action == GLFW_RELEASE) {
            v.action = -1;
        }
    }
}

void Renderer::render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.529, 0.8078, 0.922, 1);

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
    auto targetTime = std::chrono::duration<double, std::milli>(1000.0 / 120.0);

    auto lastTime = std::chrono::high_resolution_clock::now();
    auto counter = lastTime;
    frames = 0;
    do {
        auto now = std::chrono::high_resolution_clock::now();
        delta = std::chrono::duration<double, std::ratio<1>>(now - lastTime).count();
        tick();
        render();

        auto end = std::chrono::high_resolution_clock::now();
        lastTime = now;
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
    if (scene == nullptr) {
        throw std::runtime_error("Cannot transition to a null scene");
    }
    for (auto& stg : activeSceneStack) {
        stg->onDestroy();
    }
    activeSceneStack.clear();
    activeSceneStack.push_back(scene);
}

void Renderer::add(const std::shared_ptr<Scene>& scene) {
    if (scene == nullptr) {
        throw std::runtime_error("Cannot add a null scene");
    }
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

// }}}

void Renderer::refreshDisplay() {
    // WHY?!?!
    bool fullscreen = Settings::instance->getBool("fullscreen");

    // TODO: toggle fullscreen
}

} // namespace genesis
