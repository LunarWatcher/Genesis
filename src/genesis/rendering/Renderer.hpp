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
    static inline Renderer* INSTANCE;

    GLFWwindow* window;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<DefaultShader> textureShader;
    std::shared_ptr<Texture> texturePack;

    std::shared_ptr<WorldController> controller;
    std::shared_ptr<InputManager> inputManager;
    double delta;

    void initializeGame();

public:
    Renderer();

    void tick();
    void render();

    void run();

    GLFWwindow* getWindow() {
        return window;
    }

    double getDelta() {
        return delta;
    }

    auto getTextureShader() -> decltype(textureShader) {
        return textureShader;
    }

    auto getTexturePack() -> decltype(texturePack) {
        return texturePack;
    }

    auto getInputManager() -> decltype(inputManager) {
        return inputManager;
    }

    static Renderer getInstance() {
        return *INSTANCE;
    }
};

} // namespace genesis
