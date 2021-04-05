#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Model.hpp"
#include "Renderable.hpp"
#include <vector>
#include <memory>
#include "genesis/rendering/view/Camera.hpp"

namespace genesis {

class Runner;
class Renderer {
private:
    GLFWwindow* window;
    Camera camera;
    std::shared_ptr<DefaultShader> textureShader;

    Runner& runner;
public:
    std::vector<std::shared_ptr<Renderable>> objects;
    Renderer(Runner& runner);

    int initializeWindow();

    void tick();
    void render();

    GLFWwindow* getWindow() { return window; }

};

}
