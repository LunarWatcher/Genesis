#include "WorldController.hpp"

#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Entity.hpp"
#include "genesis/rendering/Model.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/Texture.hpp"
#include "genesis/rendering/environment/Chunk.hpp"
#include "genesis/world/PlayerCamp.hpp"

#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

namespace genesis {

WorldController::WorldController() : generator(std::make_shared<perlin::DumbGenerator>()) {
    WorldController::INSTANCE = this;

    controllers.push_back(std::make_shared<PlayerCamp>());
    controllers[0]->addEntity(
        std::make_shared<Entity>(Renderer::getInstance().getTexturePack()->getModel(WorldTile::COLONIST_A),
            glm::vec3{1, 0, 0}, glm::vec3{0, 0, 0}, 1));
}

void WorldController::generate() {
    auto chunk = std::make_shared<Chunk>(-1, 0);
    this->chunks.push_back(chunk);
    auto chunk2 = std::make_shared<Chunk>(0, 0);
    this->chunks.push_back(chunk2);
}

void WorldController::tick() {
    for (auto& controller : this->controllers) {
        controller->tick();
    }
}

void WorldController::render() {
    for (auto& chunk : this->chunks)
        chunk->render();

    for (auto& controller : this->controllers) {
        controller->render();
    }
}

} // namespace genesis
