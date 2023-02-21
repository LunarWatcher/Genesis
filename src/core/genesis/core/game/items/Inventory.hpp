#pragma once

#include "genesis/core/game/items/Item.hpp"
#include <memory>
#include <vector>
namespace genesis {

class Inventory {
protected:
    /**
     * Max container size. Protected by default
     */
    unsigned int size;

    std::vector<std::shared_ptr<Item>> inventory;
public:
    Inventory(unsigned int size);
    virtual ~Inventory() = default;

    // TODO: transfer function
    virtual unsigned int getMaxSize();
    virtual unsigned int getOccupiedSlots();
};

}
