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
public:
    std::vector<std::shared_ptr<Renderable>> objects;
    Renderer();
    void renderBlocking();
    int initializeWindow();

};

}
