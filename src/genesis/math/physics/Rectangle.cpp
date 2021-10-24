#include "Rectangle.hpp"

#include "genesis/rendering/Entity.hpp"
#include "spdlog/spdlog.h"

namespace genesis {

bool Rectangle::collidesWith(const Rectangle &other, bool anyZ) {
    if (!anyZ && z != other.z) return false;

    double aW = x + width,
           aH = y + height,
           bW = other.x + other.width,
           bH = other.y + other.height;
    return aW >= other.x
        && bW >= x
        && aH >= other.y
        && bH >= y;
}


void Rectangle::setDims(const double& width, const double& height) {
    this->width = width;
    this->height = height;
}

void Rectangle::update(const Entity& e) {
    auto& pos = e.getPosition();
    this->x = pos.x;
    this->y = pos.y;
    this->z = pos.z;
}

}
