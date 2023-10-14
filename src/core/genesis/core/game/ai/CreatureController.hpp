#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "genesis/core/game/ai/AIStructs.hpp"
#include "genesis/rendering/Entity.hpp"

namespace genesis {

class CreatureGroup {
private:
    // TODO: add entity IDs and convert to a map
    std::vector<std::shared_ptr<Entity>> entities;
    groupid_t groupId;
public:
    const std::string groupName;

    CreatureGroup(const std::string& groupName, groupid_t groupId);
};

/**
 * Contains and manages all the game's entities. AI control is distributed to
 * subcontrollers via this class.
 */
class CreatureController {
private:
    static std::atomic<groupid_t> CURR_RANDOM_GROUP_ID;
    std::map<groupid_t, CreatureGroup> groups;
    RelationMap creatureRelations;

    groupid_t provisionGroupId();
public:
    CreatureController();
};

}
