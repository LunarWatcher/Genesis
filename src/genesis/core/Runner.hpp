#pragma once

#include "genesis/controls/InputManager.hpp"
#include "genesis/rendering/Renderer.hpp"

namespace genesis {

class Runner {
private:
    static inline Runner* INSTANCE;
    InputManager inputManager;
    Renderer renderer;

    double delta;

    std::shared_ptr<genesis::Texture> texturePack;

public:
    Runner();

    /**
     * Manages the game loop
     */
    void runGame();

    double getDelta() {
        return delta;
    }
    static Runner* getRunner() {
        return Runner::INSTANCE;
    }

    Renderer& getRenderer() {
        return renderer;
    }
    InputManager& getInputManager() {
        return inputManager;
    }

    auto getTextureAtlas() {
        return texturePack;
    }
    void setTextureAtlas(decltype(texturePack) newTexturePack) {
        this->texturePack = newTexturePack;
    }
};

} // namespace genesis
