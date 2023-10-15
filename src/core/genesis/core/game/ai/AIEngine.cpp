#include "AIEngine.hpp"

#include "CreatureController.hpp"
#include "genesis/Context.hpp"
#include "genesis/core/game/World.hpp"

namespace genesis {

void AIEngine::simulateColony(CreatureController& cc, World& world) {
    auto entities = cc.activeColonyEntities;
    
    for (auto& [groupId, group] : entities) {
        if (groupId == 0) {
            for (auto& entity : group.getEntities()) {
                entity->getPosition().x += 1;
            }
        }
    }

}

void AIEngine::tick(CreatureController& cc, World& world) {
    simulateColony(cc, world);
}

}
