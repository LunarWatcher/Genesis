#include "Rectangle.hpp"

namespace genesis {

bool Rectangle::collidesWith(const Rectangle &other, bool anyZ) {
    if (!anyZ && z != other.z) return false;

    return (x <= other.x + other.width
            && x >= other.x
            && y <= other.y + other.height
            && y >= other.y)
        || (x + width >= other.x
            && x + width <= other.x + other.width
            && y + height >= other.y
            && y + height <= other.y + other.height
        );
}

void Rectangle::update(const Entity& e) {
    auto& pos = e.getPosition();
    this->x = pos.x - 1;
    this->y = pos.y - 1;
    this->z = pos.z;
}

}
