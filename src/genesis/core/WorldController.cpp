#include "WorldController.hpp"

#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Entity.hpp"
#include "genesis/rendering/Model.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/Texture.hpp"
#include "genesis/rendering/environment/Chunk.hpp"

#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

namespace genesis {

WorldController::WorldController() {

    auto chunk = std::make_shared<Chunk>(-1, 0);
    this->chunks.push_back(chunk);
    WorldController::INSTANCE = this;
}

void WorldController::tick() {}

void WorldController::render() {
    for (auto& chunk : this->chunks)
        chunk->render();
}

} // namespace genesis
