#include "WorldGenerator.hpp"

#include "genesis/core/game/ai/AIStructs.hpp"
#include "genesis/core/game/ai/CreatureController.hpp"
#include "genesis/core/game/generation/RNGesus.hpp"
#include "genesis/Context.hpp"

#include "genesis/core/data/DataHelper.hpp"
#include "genesis/rendering/Renderer.hpp"

namespace genesis {


std::shared_ptr<World> WorldGenerator::newWorld(int width, int height, const std::string& civName) {
    std::shared_ptr<World> world = std::make_shared<World>(width, height);
    Context::getInstance().renderer->transition(world);

    world->civilisationName = civName;

    auto& layers = world->layers;
    auto& layerMap = layers.layers;

    layerMap.insert({0, ZLayer{0, width, height}});
    auto& layer = layerMap.at(0);
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            layer.layer.at(x).at(y).floor
                = Context::getInstance().dataHelper->getTileGenerator("genesis:grass")->generateTile();
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
    auto targetY = 0;

    layerMap.at(targetY).layer.at(0).at(0).block
        = Context::getInstance().dataHelper->getTileGenerator("genesis:caravan")->generateTile();

    generateCharacters(caravanPos, world, 4);

    layers.regenerateLayerGraphics();

    return world;
}

void WorldGenerator::generateCharacters(const glm::vec3& caravanPosition, std::shared_ptr<World> world, int count) {
    world->creatures.activeColonyEntities.insert({GROUP_COLONISTS, CreatureGroup {"Colonists", GROUP_COLONISTS}});
    auto pos = caravanPosition;
    // TODO: this is why I need a proper layer structure. This fucking sucks ass
    // Future me here: there is now a layer system, but it doesn't fully account for entities.
    // This is less shit, but still not great
    pos.z += 0.01;
    for (int i = 0; i < count; ++i) {
        pos.x += 1;
        auto entity = RNGesus::genCreature(
            nullptr,
            nullptr, 
            false,
            Context::getInstance().dataLoader.creatures.at("canine")
        );
        entity->setPosition(pos);
        world->creatures.activeColonyEntities.at(GROUP_COLONISTS).pushEntity(entity);
    }
}

}
