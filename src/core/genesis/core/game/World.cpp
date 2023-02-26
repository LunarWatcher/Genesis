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
#include "genesis/math/physics/Ray.hpp"

#include <chrono>
#include <memory>
#include <functional>
#include <iostream>
#include <thread>

namespace genesis {
World::World() : generator(std::make_shared<perlin::DumbGenerator>()) {
    World::INSTANCE = this;

    registerKey(GLFW_KEY_W, 0, [](int action) {
        if (action != GLFW_PRESS) return false;
        Renderer::getInstance().getCamera()->incrementPosition(0, 10.0 * Renderer::getInstance().getDelta());
        return true;
    });
    registerKey(GLFW_KEY_A, 0, [](int action) {
        if (action != GLFW_PRESS) return false;
        Renderer::getInstance().getCamera()->incrementPosition(-10.0 * Renderer::getInstance().getDelta(), 0);
        return true;
    });
    registerKey(GLFW_KEY_S, 0, [](int action) {
        if (action != GLFW_PRESS) return false;
        Renderer::getInstance().getCamera()->incrementPosition(0, -10.0 * Renderer::getInstance().getDelta());
        return true;
    });
    registerKey(GLFW_KEY_D, 0, [](int action) {
        if (action != GLFW_PRESS) return false;
        Renderer::getInstance().getCamera()->incrementPosition(10.0 * Renderer::getInstance().getDelta(), 0);
        return true;
    });

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

std::pair<std::pair<int, int>, std::pair<int, int>> World::convertToChunkSpace(int tileX, int tileZ) {
    return {
        {
            std::floor(tileX / Constants::Chunks::CHUNK_SIZE),
                std::floor(tileZ / Constants::Chunks::CHUNK_SIZE),
        },
            {
                tileX % Constants::Chunks::CHUNK_SIZE,
                tileZ % Constants::Chunks::CHUNK_SIZE
            }
    };
}

} // namespace genesis
