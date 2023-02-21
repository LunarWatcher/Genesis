#include "Rectangle.hpp"

#include <glm/glm.hpp>

namespace genesis {

bool Rectangle::collidesWith(const Rectangle &other, bool anyZ) {
    if (!anyZ && z != other.z) return false;

    double aW = x + width,
           aH = y + height,
           bW = other.x + other.width,
           bH = other.y + other.height;
    return other.x >= x
        && other.y >= y
        && other.x <= aW
        && other.y <= aH;
}


void Rectangle::setDims(const double& width, const double& height) {
    this->width = width;
    this->height = height;
}

void Rectangle::update(const glm::vec3& pos) {
    this->x = pos.x;
    this->y = pos.y;
    this->z = pos.z;
}

}
