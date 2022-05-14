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
    // TODO: hook these up to an option or something.
    // Might be worth doing a scaling factor (i.e. this is a medium world, small worlds are these mulitplied by 0.5, large is multiplied by 2, huge by 4, or
    // something. Idk, figure it out, future me)
    // TODO: add disk caching and sane world generation
    int xChunks = 30;
    int yChunks = 20;
    entityControllers.push_back(std::make_shared<PlayerCamp>());
    // TODO: add a chunk controller, though I'm not sure how we want to do that.
    // It's heavily state-dependent, but I think we're good as long as all the chunks have collisions.

    // I don't know how the coordinate systems should work

    chunks.push_back(std::make_shared<Chunk>(0, 0));
    //for (long long x = -xChunks / 2; x <= xChunks / 2; ++x) {
        //for (long long y = -yChunks / 2; y <= yChunks; ++y) {
            //auto chunk = std::make_shared<Chunk>(x, y);
            //chunks.push_back(chunk);
        //}
    //}

}

void WorldController::tick() {
    for (auto& controller : this->entityControllers)
        controller->tick();
}

void WorldController::render() {
    Renderer& inst = Renderer::getInstance();
    inst.getTextureShader()->apply();
    inst.getTexturePack()->bind();

    for (auto& controller : this->entityControllers)
        controller->render();

    for (auto& chunk : this->chunks)
        chunk->render();

    inst.getTexturePack()->unbind();
    inst.getTextureShader()->stop();
}

const std::vector<std::shared_ptr<EntityController>>& WorldController::getEntityControllers() {
    return entityControllers;
}

} // namespace genesis
