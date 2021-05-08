#include "Perlin.hpp"

namespace perlin {

NoiseGenerator::NoiseGenerator() {
    seed = rawRandom();
    gen = std::mt19937(seed);
}

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

void Perlin2DNoiseGenerator::generateChunk(genesis::ChunkMap& ref, int chunkX, int chunkY) {}

} // namespace perlin
