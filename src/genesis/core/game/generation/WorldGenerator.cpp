#include "WorldGenerator.hpp"

#include "genesis/rendering/Renderer.hpp"
#include "genesis/world/PlayerCamp.hpp"
#include "genesis/core/game/entities/Colonist.hpp"

namespace genesis {


std::shared_ptr<World> WorldGenerator::newWorld(int xChunks, int yChunks, const std::string& civName) {
    std::shared_ptr<World> world = std::make_shared<World>();
    Renderer::getInstance().transition(world);

    world->civilisationName = civName;
    
    world->entityControllers.push_back(std::make_shared<PlayerCamp>());

    auto& controller = world->entityControllers.back();
    controller->addEntity(
        std::make_shared<Colonist>("genesis:colonist_a", "Sparta",
            glm::vec3{0, 0, 0.1},
            25 // semi-random age; idk, 25 seems like a reasonable age for our first citizens
        )
    );

    // TODO: add a ChunkController as well. This is deeper down the world management rabbit hole
    for (long long x = -xChunks / 2; x <= xChunks / 2; ++x) {
        for (long long y = -yChunks / 2; y <= yChunks; ++y) {
            auto chunk = std::make_shared<Chunk>(x, y);
            world->chunks.push_back(chunk);
        }
    }
    

    return world;
}

}
