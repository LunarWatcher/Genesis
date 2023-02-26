#pragma once

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

    // TODO: replace with a different container. Vectors aren't really a good idea for this.
    std::vector<std::shared_ptr<Chunk>> chunks;
    std::vector<std::shared_ptr<EntityController>> entityControllers;

public:
    World();

    void render() override;
    void tick() override;

    std::shared_ptr<perlin::NoiseGenerator> getNoiseGenerator() {
        return generator;
    }

    /**
     * Returns world coordinates as chunk coords, and coords within the chunk
     */
    std::pair<std::pair<int, int>, std::pair<int, int>> convertToChunkSpace(int tileX, int tileZ);

    const std::vector<std::shared_ptr<EntityController>>& getEntityControllers() override;

    friend class WorldGenerator;
};

} // namespace genesis
