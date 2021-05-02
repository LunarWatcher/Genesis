#pragma once

#include "genesis/controls/InputManager.hpp"
#include "genesis/rendering/Renderer.hpp"

namespace genesis {

class WorldController {
private:
    static inline WorldController* INSTANCE;
    InputManager inputManager;
    Renderer renderer;

    double delta;

    std::shared_ptr<genesis::Texture> texturePack;

public:
    WorldController();

    /**
     * Manages the game loop
     */
    void runGame();

    double getDelta() {
        return delta;
    }
    static WorldController* getWorld() {
        return WorldController::INSTANCE;
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
