#include "AIEngine.hpp"

#include "CreatureController.hpp"
#include "genesis/Context.hpp"
#include "genesis/core/game/World.hpp"
#include "genesis/core/game/generation/RNGesus.hpp"

namespace genesis {

void AIEngine::simulateColony(CreatureController& cc, World& world) {
    auto entities = cc.activeColonyEntities;
    
    for (auto& [groupId, group] : entities) {
        if (groupId == 0) {
            for (auto& entity : group.getEntities()) {
                auto newPosition = entity->getPosition();
                newPosition.x += util::randInt(-1, 1);
                newPosition.y += util::randInt(-1, 1);
                if (world.layers.canMove(entity->getPosition(), newPosition)) {
                    entity->setPosition(newPosition);
                }
            }
        }
    }

}

void AIEngine::tick(CreatureController& cc, World& world) {
    simulateColony(cc, world);
}

}
