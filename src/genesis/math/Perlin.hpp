#include "genesis/rendering/environment/Chunk.hpp"
#include <math.h>
#include <random>
#include <utility>
#include <vector>

namespace perlin {

class NoiseGenerator {
protected:
    long seed;

    // Random stuff
    std::random_device rawRandom{};
    std::mt19937 gen;

    std::uniform_real_distribution<double> distGenerator{-1, 1};

public:
    NoiseGenerator();
    NoiseGenerator(long seed) : seed(seed), gen(seed) {}

    virtual ~NoiseGenerator() = default;

    virtual void generateChunk(genesis::ChunkMap& ref, int chunkX, int chunkY) = 0;

    long getSeed() {
        return seed;
    }
};

class Perlin2DNoiseGenerator : public NoiseGenerator {
public:
    Perlin2DNoiseGenerator(long seed) : NoiseGenerator(seed) {}
    virtual double interpolate(double a0, double a1, double w);
    virtual std::pair<double, double> randomVector();

    virtual void generateChunk(genesis::ChunkMap& ref, int chunkX, int chunkY) override;
};

} // namespace perlin
