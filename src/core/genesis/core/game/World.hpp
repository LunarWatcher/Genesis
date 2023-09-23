#pragma once


#include "genesis/core/game/chunks/MapLayers.hpp"
#include "genesis/core/game/entities/GameCreature.hpp"
#include "genesis/rendering/gl/Framebuffer.hpp"
#include "genesis/world/EntityController.hpp"
#include "genesis/rendering/flow/Scene.hpp"

#include "genesis/math/Perlin.hpp"
#include <string>

#include "GLFW/glfw3.h"

namespace genesis {

class Chunk;

class World : public Scene {
private:
    static inline World* INSTANCE = nullptr;

    std::shared_ptr<perlin::NoiseGenerator> generator;
    //std::shared_ptr<Framebuffer> frame;

    // Game state
    std::string civilisationName;

    MapLayers layers;
    std::vector<std::shared_ptr<GameCreature>> gameEntities;

    static double getScrollAcceleratorCoefficient(int mods) {
        if (mods &= GLFW_MOD_SHIFT) {
            return 3.0;
        }
        return 1.0;
    }
public:
    World(int width, int height);

    void render() override;
    void tick() override;

    std::shared_ptr<perlin::NoiseGenerator> getNoiseGenerator() {
        return generator;
    }

    /**
     * Returns world coordinates as chunk coords, and coords within the chunk
     */
    std::pair<std::pair<int, int>, std::pair<int, int>> convertToChunkSpace(int tileX, int tileZ);

    friend class WorldGenerator;
};

} // namespace genesis
