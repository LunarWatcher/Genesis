#pragma once

#include "genesis/controls/InputManager.hpp"
#include "genesis/rendering/environment/Chunk.hpp"
#include "genesis/world/EntityController.hpp"
#include "genesis/rendering/flow/Scene.hpp"

#include "genesis/math/Perlin.hpp"

namespace genesis {

class Chunk;
class WorldController : public Scene {
private:
    static inline WorldController* INSTANCE = nullptr;

    std::vector<std::shared_ptr<Chunk>> chunks;
    std::vector<std::shared_ptr<EntityController>> entityControllers;
    std::shared_ptr<perlin::NoiseGenerator> generator;

public:
    WorldController();

    void generate();

    void render() override;
    void tick() override;

    std::shared_ptr<perlin::NoiseGenerator> getNoiseGenerator() {
        return generator;
    }

    const std::vector<std::shared_ptr<EntityController>>& getEntityControllers() override;
};

} // namespace genesis
