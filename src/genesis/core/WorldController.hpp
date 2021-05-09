#pragma once

#include "genesis/controls/InputManager.hpp"
#include "genesis/rendering/environment/Chunk.hpp"
#include "genesis/world/EntityController.hpp"

#include "genesis/math/Perlin.hpp"

namespace genesis {

class Chunk;
class WorldController {
private:
    static inline WorldController* INSTANCE = nullptr;
    static inline constexpr int MS_PER_DAY = 20'000;

    int timeOfDay;

    std::vector<std::shared_ptr<Chunk>> chunks;
    std::vector<EntityController> controllers;
    perlin::Perlin2DNoiseGenerator generator;

public:
    WorldController();

    void generate();

    void render();
    void tick();

    perlin::Perlin2DNoiseGenerator& getNoiseGenerator() {
        return generator;
    }
};

} // namespace genesis
