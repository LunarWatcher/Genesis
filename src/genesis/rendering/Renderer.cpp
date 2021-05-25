#include "Renderer.hpp"

#include "GLFW/glfw3.h"

#include "Shader.hpp"
#include "genesis/core/WorldController.hpp"
#include "genesis/rendering/Texture.hpp"
#include "shaders/DefaultShader.hpp"
#include FT_FREETYPE_H

#include <chrono>
#include <iostream>
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

    initGame();
    initFonts();
}

void Renderer::initGame() {
    this->inputManager = std::make_shared<InputManager>();
    this->camera = std::make_shared<Camera>();

    this->texturePack = std::make_shared<genesis::WorldTexture>("images/programmer.png");

    this->worldController = std::make_shared<WorldController>();
    this->worldController->generate();

    this->textureShader = std::make_shared<DefaultShader>();
    this->textShader = std::make_shared<TextShader>();

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
    auto error = FT_Init_FreeType(&this->fontLibrary);
    // I'll never understand what it is with these libraries and their shitty error handling.
    // Just give me some useful error that actually explains what went wrong :rolling_eyes:
    // Doesn't have to include a fix, but a string already beats a whatever the fuck
    // error is here, and whatever the fuck error is in GLFW.
    if (error) {
        std::cerr << "An error occured when initializing the font library" << std::endl;
        throw std::runtime_error("Font initialization failed");
    }
}

void Renderer::tick() {
    worldController->tick();
}

void Renderer::render() {

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 0, 1, 1);

    textureShader->apply();
    texturePack->bind();
    camera->applyCamera(*textureShader);

    worldController->render();

    texturePack->unbind();
    textureShader->stop();

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
        if (sleepFor > std::chrono::milliseconds(0))
            std::this_thread::sleep_for(sleepFor);
    } while (glfwWindowShouldClose(window) == 0);

    glfwTerminate();
}

} // namespace genesis
