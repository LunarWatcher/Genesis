#pragma once

#include <GL/glew.h>
#include <vector>

namespace genesis {
namespace Constants {

inline const std::vector<GLfloat> square = {0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f};
inline const std::vector<GLint> squareIndices = {0, 1, 3, 3, 1, 2};

inline constexpr int MAX_OVERWORLD_HEIGHT = 32;
inline constexpr int MAX_UNDERGROUND_HEIGHT = 32;
inline constexpr int FLAT_COMPENSATION_FACTOR = 15;

} // namespace Constants
} // namespace genesis
