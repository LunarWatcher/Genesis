#pragma once

#include "genesis/core/game/ai/AIStructs.hpp"
#include "genesis/rendering/Entity.hpp"
#include <memory>
#include <vector>

namespace genesis {

class EntityGroup {
private:
    std::vector<std::shared_ptr<Entity>> entities;

    std::string groupName;
    groupid_t groupId;
};

}
