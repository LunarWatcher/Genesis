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
}

void WorldController::generate() {
    entityControllers.push_back(std::make_shared<PlayerCamp>());
    entityControllers[0]->addEntity(
        std::make_shared<Entity>(Renderer::getInstance().getTexturePack()->getModel(WorldTile::COLONIST_A),
            glm::vec3{2, 2, 0.1}, glm::vec3{0, 0, 0}, 1));

    auto chunk = std::make_shared<Chunk>(-1, 0);

    this->chunks.push_back(chunk);
    auto chunk2 = std::make_shared<Chunk>(0, 0);

    this->chunks.push_back(chunk2);

}

void WorldController::tick() {
    for (auto& controller : this->entityControllers)
        controller->tick();
}

void WorldController::render() {
    Renderer& inst = Renderer::getInstance();
    inst.getTextureShader()->apply();
    inst.getTexturePack()->bind();
    for (auto& chunk : this->chunks)
        chunk->render();

    for (auto& controller : this->entityControllers)
        controller->render();
    inst.getTexturePack()->unbind();
    inst.getTextureShader()->stop();
}

const std::vector<std::shared_ptr<EntityController>>& WorldController::getEntityControllers() {
    return entityControllers;
}

} // namespace genesis
