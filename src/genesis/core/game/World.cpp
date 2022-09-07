#include "World.hpp"

#include "genesis/core/game/generation/WorldGenerator.hpp"
#include "genesis/core/game/entities/Colonist.hpp"
#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Entity.hpp"
#include "genesis/rendering/Model.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/Texture.hpp"
#include "genesis/rendering/environment/Chunk.hpp"
#include "genesis/world/PlayerCamp.hpp"

#include <chrono>
#include <memory>
#include <functional>
#include <iostream>
#include <thread>

namespace genesis {
World::World() : generator(std::make_shared<perlin::DumbGenerator>()) {
    World::INSTANCE = this;
}

void World::tick() {
    for (auto& controller : this->entityControllers)
        controller->tick();
}

void World::render() {
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

const std::vector<std::shared_ptr<EntityController>>& World::getEntityControllers() {
    return entityControllers;
}

} // namespace genesis
