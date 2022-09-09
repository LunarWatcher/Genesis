#include "Inventory.hpp"

namespace genesis {

Inventory::Inventory(unsigned int size) : size(size) {
}

unsigned int Inventory::getMaxSize() {
    return size;
}

unsigned int Inventory::getOccupiedSlots() {
    return inventory.size();
}

}
