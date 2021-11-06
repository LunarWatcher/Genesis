#include "Chunk.hpp"
#include "genesis/core/WorldController.hpp"
#include "genesis/math/Perlin.hpp"
#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/shaders/DefaultShader.hpp"

namespace genesis {

Chunk::Chunk(int chunkX, int chunkY) : chunkX(chunkX), chunkY(chunkY) {
    Renderer::getInstance().getSceneByType<WorldController>()->getNoiseGenerator()->generateChunk(this->chunkMap, chunkX, chunkY);

    //this->model = std::make_shared
}

void Chunk::render() {
    if (!chunkMap.contains(Renderer::getInstance().getCamera()->getActiveY()))
        return;
    auto& currLevel = chunkMap.at(Renderer::getInstance().getCamera()->getActiveY());



    for (auto& vec : currLevel) {
        for (auto& entity : vec) {
            if (entity != -1) {

            }
        }
    }
}

} // namespace genesis
