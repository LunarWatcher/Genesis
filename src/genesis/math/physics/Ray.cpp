#include "Ray.hpp"
#include "genesis/math/physics/Rectangle.hpp"

namespace genesis {

Ray::Ray(const glm::vec3& startPos, const glm::vec3& direction)
        : Rectangle(startPos.x, startPos.y, startPos.z, 1, 1),
        direction(direction) {}

}
