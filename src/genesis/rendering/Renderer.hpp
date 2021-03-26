#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "RenderObject.hpp"
#include <vector>
#include <memory>

namespace genesis {

class Renderer {
private:
    GLFWwindow* window;
public:
    std::vector<std::shared_ptr<RenderObject>> objects;
    Renderer();
    void renderBlocking();
    int initializeWindow();

};

}
