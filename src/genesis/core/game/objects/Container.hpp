#pragma once

#include "genesis/rendering/Entity.hpp"
#include "genesis/core/game/items/Item.hpp"
#include "genesis/core/game/items/Inventory.hpp"

#include <string>
#include <vector>

namespace genesis {

class Container : public Entity, public Inventory {
protected:
    std::string texId;

public:
    Container(const std::string texId, const unsigned int slots);


};

}
