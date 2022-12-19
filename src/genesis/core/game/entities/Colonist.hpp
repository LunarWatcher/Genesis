#pragma once

#include "genesis/core/game/items/Inventory.hpp"
#include "genesis/core/game/items/Item.hpp"
#include "genesis/rendering/Entity.hpp"

#include "genesis/core/game/log/Date.hpp"

namespace genesis {

class Colonist : public Entity, public Inventory {
public:
    // Variables {{{
    // Internal management {{{
    std::string textureName;
    // }}}

    // Colonist attributes {{{
    std::string colonistName;
    
    Date birthDate;
    size_t age;

    unsigned int hitpoints;
    unsigned int armor;

    bool alive;

    // }}}
    // }}}
    Colonist(const std::string& textureName, const std::string& colonistName, const glm::vec3& spawnPosition, size_t age, unsigned int hitpoints = 100, unsigned int armor = 0);

};

}
