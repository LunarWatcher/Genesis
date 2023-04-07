#pragma once

#include "glm/vec3.hpp"

#include <memory>
#include <random>

namespace genesis {

// Forward declarations, because this file is severely prone to forward declaration problems.
class Colonist;
class World;

namespace RNGesus {

namespace _random {

inline std::random_device dev;
inline std::default_random_engine engine(dev());

}

}

}
