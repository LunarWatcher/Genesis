#pragma once

#include "genesis/conf/Settings.hpp"
#include "genesis/math/physics/Rectangle.hpp"
#include "genesis/rendering/Renderer.hpp"
#include <cmath>

namespace genesis {

namespace Ray {


extern glm::vec2 normalizeScreenCoords(double x, double y);
extern void traceClick(const glm::vec2& rawCoords, const glm::vec2& normalizedScreenCoords);

}

}
