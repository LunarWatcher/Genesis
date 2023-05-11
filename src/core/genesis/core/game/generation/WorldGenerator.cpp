#include "WorldGenerator.hpp"

#include "genesis/core/game/generation/RNGesus.hpp"
#include "genesis/Context.hpp"

#include "genesis/core/data/DataHelper.hpp"
#include "genesis/rendering/Renderer.hpp"

namespace genesis {


std::shared_ptr<World> WorldGenerator::newWorld(int xChunks, int yChunks, const std::string& civName) {
    std::shared_ptr<World> world = std::make_shared<World>();
    Context::getInstance().renderer->transition(world);

    world->civilisationName = civName;
    
    for (long long x = -xChunks / 2; x <= xChunks / 2; ++x) {
        for (long long y = -yChunks / 2; y <= yChunks; ++y) {
            auto chunk = std::make_shared<Chunk>(x, y);
            world->chunks.push_back(chunk);
        }
    }

    // Caravan spawning defines the spawn function. I imagine this has to change when world generation
    // becomes complicated, and possibly expands into full world generation with local picks for the
    // actual base area (i.e. Dwarf Fortress-like mechanics)
    //
    // Or even just get a moderately complex spawn area and need to be smarter with the proper spawn chunk
    // The reality though, is that it doesn't matter. The caravan just needs to be somewhere accessible
    // seeing as it's the start site for the colonists.
    // seeing as there currently isn't any world gen, chunk 0 is fine.
    glm::vec3 caravanPos{0, 0, 0};
    for (auto& chunk : world->chunks) {
        if (chunk->getX() == 0 && chunk->getY() == 0) {
            auto targetY = chunk->getTopY(0, 0) + 1;
            
            chunk->set(
                Context::getInstance().dataHelper->getTileGenerator("genesis:caravan")->generateTile(),
                0, 0,
                targetY
            );
        }
    }

    generateCharacters(caravanPos, world, 4);

    return world;
}

void WorldGenerator::generateCharacters(const glm::vec3& caravanPosition, std::shared_ptr<World> world, int count) {
    auto pos = caravanPosition;
    // TODO: this is why I need a proper layer structure. This fucking sucks ass
    pos.z += 1;
    for (int i = 0; i < count; ++i) {
        pos.x += 1;
        auto entity = RNGesus::genCreature(
            nullptr,
            nullptr, 
            false,
            Context::getInstance().dataLoader.creatures.at("canine")
        );
        entity->setPosition(pos);
        world->gameEntities.push_back(entity);
    }
}

}
