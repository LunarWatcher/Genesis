#include "CreatureController.hpp"
#include "genesis/core/game/ai/CreatureController.hpp"

namespace genesis {
// CreatureGroup {{{
CreatureGroup::CreatureGroup(const std::string& groupName, groupid_t groupId) : groupName(groupName), groupId(groupId) {

}

void CreatureGroup::render() {
    for (auto& entity : this->entities) {
        entity->render();
    }
}
void CreatureGroup::tick() {
    for (auto& entity : this->entities) {
        entity->tick();
    }
}

void CreatureGroup::pushEntity(std::shared_ptr<GameCreature> creature) {
    // TODO: update the group_id to this when pushing
    this->entities.push_back(creature);
}
// }}}
// CreatureController {{{
CreatureController::CreatureController() {

}

groupid_t CreatureController::provisionGroupId() {
    return CreatureController::CURR_RANDOM_GROUP_ID.fetch_add(1);
}

void CreatureController::render() {
    for (auto& [_, creatureGroup] : groups) {
        creatureGroup.render();
    }
}

void CreatureController::tick() {
    for (auto& [_, creatureGroup] : groups) {
        creatureGroup.render();
    }
}
// }}}
}
