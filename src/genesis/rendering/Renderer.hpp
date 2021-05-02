#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Model.hpp"
#include "Renderable.hpp"
#include "genesis/rendering/view/Camera.hpp"
#include <memory>
#include <vector>

namespace genesis {

class WorldController;
class Renderer {
private:
    GLFWwindow* window;
    Camera camera;
    std::shared_ptr<DefaultShader> textureShader;

    WorldController& runner;

public:
    std::vector<std::shared_ptr<Renderable>> objects;
    Renderer(WorldController& runner);

    int initializeWindow();

    void tick();
    void render();

    GLFWwindow* getWindow() {
        return window;
    }
};

} // namespace genesis
