#pragma once

#include "genesis/math/physics/Rectangle.hpp"
#include "glm/ext/vector_float3.hpp"

namespace genesis {

class Ray : public Rectangle {
private:
    glm::vec3 startPosition, direction;
public:
    Ray(const glm::vec3& startPos, const glm::vec3& direction);
};

}
