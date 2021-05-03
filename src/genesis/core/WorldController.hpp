#pragma once

#include "genesis/controls/InputManager.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/environment/Chunk.hpp"
#include "genesis/world/EntityController.hpp"

namespace genesis {

class Chunk;
class WorldController {
private:
    static inline WorldController* INSTANCE = nullptr;
    static inline constexpr int MS_PER_DAY = 20'000;

    std::shared_ptr<genesis::Texture> texturePack;

    InputManager inputManager;
    Renderer renderer;

    double delta;

    int timeOfDay;

    std::vector<std::shared_ptr<Chunk>> chunks;
    std::vector<EntityController> controllers;

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
