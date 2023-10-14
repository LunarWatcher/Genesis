#pragma once

#include <map>
#include <utility>

namespace genesis {

enum class CreatureRelations {
    HOSTILE,
    NEUTRAL,
    FRIENDLY,
};

enum class CivRelations {
    WAR,
    HOSTILE,
    NEUTRAL,
    FRIENDLY,
    ALLY,
};

using groupid_t = int;
static inline constexpr auto GROUP_COLONISTS = 0;
// Groups 0-99 are reserved for static groups
static inline constexpr auto GROUP_RANDOM_STARTIDX = 100;

using RelationMap = std::map<std::pair<groupid_t, groupid_t>, CreatureRelations>;


}
