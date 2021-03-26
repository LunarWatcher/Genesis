#include "Renderer.hpp"
#include "Shader.hpp"
#include <iostream>
#include "genesis/rendering/Texture.hpp"
#include "shaders/DefaultShader.hpp"

namespace genesis {

Renderer::Renderer() {
    
}

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

    this->window = glfwCreateWindow(1024, 768, "Genesis", nullptr, nullptr);
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
    //glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    return 0;
}

void Renderer::renderBlocking() {
    if (this->window == nullptr) {
        throw std::runtime_error("Window is a nullptr");
    }
    DefaultShader shader;
    do {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1, 0, 1, 1);

        shader.apply();
        for (auto& object : objects) {
            object->render();
        }
        shader.stop();

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwWindowShouldClose(this->window) == 0);
}

}
