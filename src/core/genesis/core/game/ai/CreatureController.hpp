#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "genesis/core/game/ai/AIStructs.hpp"
#include "genesis/core/game/entities/GameCreature.hpp"
#include "genesis/rendering/Entity.hpp"

namespace genesis {

class CreatureGroup {
private:
    // TODO: add entity IDs and convert to a map
    std::vector<std::shared_ptr<GameCreature>> entities;
    groupid_t groupId;
public:
    const std::string groupName;

    CreatureGroup(const std::string& groupName, groupid_t groupId);

    void render();
    void tick();

    void pushEntity(std::shared_ptr<GameCreature> creature);
    
};

/**
 * Contains and manages all the game's entities. AI control is distributed to
 * subcontrollers via this class.
 *
 * The class is split into two: creatures actively part of the game, and 
 * creatures part of the world history but not in the current colony. The latter
 * group is simulated with a much lower resolution.
 * Or at least will be. At the time of writing, world entities have not been implemented yet.
 */
class CreatureController {
private:
    static inline std::atomic<groupid_t> CURR_RANDOM_GROUP_ID{GROUP_RANDOM_STARTIDX};
    RelationMap creatureRelations;

    groupid_t provisionGroupId();
public:
    std::map<groupid_t, CreatureGroup> groups;

    CreatureController();

    void render();
    void tick();
};

}
