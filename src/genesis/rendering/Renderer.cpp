#include "Renderer.hpp"
#include "GLFW/glfw3.h"
#include "Shader.hpp"
#include "genesis/core/Runner.hpp"
#include "genesis/rendering/Texture.hpp"
#include "shaders/DefaultShader.hpp"
#include <chrono>
#include <iostream>
#include <thread>

namespace genesis {

Renderer::Renderer(Runner& runner) : camera(runner.getInputManager()), runner(runner) {}

int Renderer::initializeWindow() {
    glewExperimental = true;
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
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
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW." << std::endl;
        return -1;
    }

    this->textureShader = std::make_shared<DefaultShader>();

    return 0;
}

void Renderer::tick() {}

void Renderer::render() {

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 0, 1, 1);

    textureShader->apply();
    camera.applyCamera(*textureShader);
    for (auto& object : objects) {
        object->render(*textureShader);
    }
    textureShader->stop();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

} // namespace genesis
