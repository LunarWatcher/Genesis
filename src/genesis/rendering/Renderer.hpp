#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Model.hpp"
#include "Renderable.hpp"
#include <vector>
#include <memory>
#include "genesis/rendering/view/Camera.hpp"

namespace genesis {

class Renderer {
private:
    GLFWwindow* window;
    Camera camera;
    std::shared_ptr<DefaultShader> textureShader;

public:
    std::vector<std::shared_ptr<Renderable>> objects;
    Renderer();

    int initializeWindow();

    void tick();
    void render();

    GLFWwindow* getWindow() { return window; }

};

}
