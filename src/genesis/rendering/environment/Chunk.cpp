#include "Chunk.hpp"
#include "genesis/math/Perlin.hpp"
#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/shaders/DefaultShader.hpp"

namespace genesis {

Chunk::Chunk(int chunkX, int chunkY) : chunkX(chunkX), chunkY(chunkY) {
    perlin::Perlin2DNoiseGenerator{0}.generateChunk(this->chunkMap, chunkX, chunkY);
}

void Chunk::render() {
    if (!chunkMap.contains(Renderer::getInstance().getCamera()->getActiveY()))
        return;
    auto& currLevel = chunkMap.at(Renderer::getInstance().getCamera()->getActiveY());

    for (auto& vec : currLevel) {
        for (auto& entity : vec) {
            if (entity == nullptr)
                continue;
            entity->render();
        }
    }
}

} // namespace genesis
