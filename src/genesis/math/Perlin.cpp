#include "Perlin.hpp"
#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Entity.hpp"
#include "genesis/rendering/Renderer.hpp"
#include <iostream>

namespace perlin {

NoiseGenerator::NoiseGenerator() {
    seed = rawRandom();
    gen = std::mt19937(seed);
}

// 2D perlin noise {{{
/**
 * Interpolation using smoothing.
 */
double Perlin2DNoiseGenerator::interpolate(double a0, double a1, double w) {
    return (a1 - a0) * w + a0;
}

std::pair<double, double> Perlin2DNoiseGenerator::randomVector() {
    // clang-format off
    return {
        distGenerator(gen),
        distGenerator(gen)
    };
    // clang-format on
}

double Perlin2DNoiseGenerator::dotGridGradient(int ix, int iy, double x, double y) {
    auto vec = randomVector();

    double deltaX = x - (double) ix;
    double deltaY = y - (double) iy;

    return deltaX * vec.first + deltaY * vec.second;
}

double Perlin2DNoiseGenerator::perlin(double x, double y) {
    int x0 = std::floor(x);
    int x1 = x0 + 1;

    int y0 = std::floor(y);
    int y1 = y0 + 1;

    double sx = x - (double) x0;
    double sy = y - (double) y0;

    double n0 = dotGridGradient(x0, y0, x, y);
    double n1 = dotGridGradient(x1, y0, x, y);
    double ix0 = interpolate(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    double ix1 = interpolate(n0, n1, sx);

    return interpolate(ix0, ix1, sy);
}

int Perlin2DNoiseGenerator::clampPerlin(double perlinInput) {
    // Get the noise in [0, 1]
    auto clampedPerlin = (perlinInput + 1) / 2;
    // Generate the range
    auto normalizedPerlin = std::floor(
            clampedPerlin * (genesis::Constants::MAX_OVERWORLD_HEIGHT + genesis::Constants::FLAT_COMPENSATION_FACTOR));

    // This is potentially possible to modify with biomes, but that's a problem for later
    if (normalizedPerlin >= 10 && normalizedPerlin <= 10 + genesis::Constants::FLAT_COMPENSATION_FACTOR) {
        normalizedPerlin = 10;
    } else if (normalizedPerlin > 10 + genesis::Constants::FLAT_COMPENSATION_FACTOR) {
        normalizedPerlin -= genesis::Constants::FLAT_COMPENSATION_FACTOR;
    }
    return normalizedPerlin;
}

void Perlin2DNoiseGenerator::generateChunk(genesis::ChunkMap& ref, int chunkX, int chunkY) {
    constexpr double STEP_DISTANCE = 1.0 / genesis::Chunk::CHUNK_SIZE;

    auto rawObject = std::make_shared<genesis::Model>(genesis::Constants::square, [&](genesis::Model* model) {
        model->bindIndexBuffer(genesis::Constants::squareIndices);
        model->createVBO(1, 2, genesis::Renderer::getInstance().getTexturePack()->generateFromPosition(0, 12, 64, 64));
    });

    for (size_t y = 0; y < genesis::Constants::MAX_OVERWORLD_HEIGHT; ++y) {
        auto& cLevel = ref[y];
        cLevel.resize(genesis::Chunk::CHUNK_SIZE);

        for (size_t z = 0; z < genesis::Chunk::CHUNK_SIZE; ++z) {
            auto& vec = cLevel.at(z);
            for (int x = 0; x < genesis::Chunk::CHUNK_SIZE; ++x) {
                vec.resize(genesis::Chunk::CHUNK_SIZE);
            }
        }
    }

    // Coordinates relative to the chunk border: used for coordinate generation and accessing the map
    int rx = 0, rz = 0;
    for (double z = chunkY + STEP_DISTANCE; z <= chunkY + 16 * STEP_DISTANCE; z += STEP_DISTANCE) {
        for (double x = chunkX + STEP_DISTANCE; x <= chunkX + 16 * STEP_DISTANCE; x += STEP_DISTANCE) {
            int y = clampPerlin(perlin(x, z));
            ref[y][rz][rx] = std::make_shared<genesis::Entity>(rawObject,
                    glm::vec3{chunkX * genesis::Chunk::CHUNK_SIZE + rx, chunkY * genesis::Chunk::CHUNK_SIZE + rz, -3});
            rx++;
        }
        rx = 0;
        rz++;
    }
}
// }}}
// DumbGenerator {{{
void DumbGenerator::generateChunk(genesis::ChunkMap& ref, int chunkX, int chunkY) {
    auto tile = genesis::Renderer::getInstance().getTexturePack()->getModel(genesis::WorldTile::GRASS);
    // We pick 0 as the primary level
    auto& activeLevel = ref[0];
    // resize y to match the chunk size
    activeLevel.resize(genesis::Chunk::CHUNK_SIZE);
    for (int z = 0; z < genesis::Chunk::CHUNK_SIZE; ++z) {
        // and resize the x coords for a given y
        activeLevel[z].resize(genesis::Chunk::CHUNK_SIZE);

        for (int x = 0; x < genesis::Chunk::CHUNK_SIZE; ++x) {

            activeLevel[z][x] = std::make_shared<genesis::Entity>(tile,
                    glm::vec3{chunkX * genesis::Chunk::CHUNK_SIZE + x, chunkY * genesis::Chunk::CHUNK_SIZE + z, 0});
        }
    }
}
// }}}

} // namespace perlin
