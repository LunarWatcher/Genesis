#include "CreatureController.hpp"

namespace genesis {
// CreatureGroup {{{
CreatureGroup::CreatureGroup(const std::string& groupName, groupid_t groupId) : groupName(groupName), groupId(groupId) {

}
// }}}
// CreatureController {{{
CreatureController::CreatureController() {

}

groupid_t CreatureController::provisionGroupId() {
    return CreatureController::CURR_RANDOM_GROUP_ID.fetch_add(1);
}

CreatureGroup& CreatureController::getCreatureGroup(groupid_t id) {
    return groups.at(id);
}
// }}}
}
