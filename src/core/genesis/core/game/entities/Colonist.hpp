#pragma once

#include "genesis/core/game/items/Inventory.hpp"
#include "genesis/core/game/items/Item.hpp"
#include "genesis/rendering/Entity.hpp"

#include "genesis/core/data/ColonistAttribs.hpp"

namespace genesis {


class Colonist : public Entity, public Inventory {
public:
    // Variables {{{
    // Internal management {{{
    std::string textureName;
    // }}}

    // Colonist attributes {{{
    std::string colonistName;
    
    size_t age;

    unsigned int hitpoints;
    unsigned int armor;

    bool alive;

    ColonistGenes genes;

    // }}}
    // }}}
    Colonist(const ColonistGenes& genes,
             const std::string& colonistName,
             const glm::vec3& spawnPosition,
             size_t age,
             unsigned int hitpoints = 100,
             unsigned int armor = 0);


    std::string pickTexture();
    void updateTexture();
};

}