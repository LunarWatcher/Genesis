#pragma once

#include "genesis/controls/InputManager.hpp"
#include "genesis/rendering/environment/Chunk.hpp"
#include "genesis/world/EntityController.hpp"
#include "genesis/rendering/flow/Scene.hpp"

#include "genesis/math/Perlin.hpp"
#include <string>

namespace genesis {

class Chunk;

class World : public Scene {
private:
    static inline World* INSTANCE = nullptr;

    std::shared_ptr<perlin::NoiseGenerator> generator;

    // Game state
    std::string civilisationName;

    std::vector<std::shared_ptr<Chunk>> chunks;
    std::vector<std::shared_ptr<EntityController>> entityControllers;

public:
    World();

    void render() override;
    void tick() override;

    std::shared_ptr<perlin::NoiseGenerator> getNoiseGenerator() {
        return generator;
    }

    const std::vector<std::shared_ptr<EntityController>>& getEntityControllers() override;

    friend class WorldGenerator;
};

} // namespace genesis
