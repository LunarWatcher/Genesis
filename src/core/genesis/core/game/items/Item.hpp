#pragma once

#include <string>

namespace genesis {

/**
 * Represents an inventory item for a character.
 */
class Item {
public:
    std::string itemId;

    unsigned int quantity;

    Item(const std::string& itemId, unsigned int initialQuantity) : itemId(itemId),
            quantity(initialQuantity) {}

};

}
