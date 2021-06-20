#pragma once

#include <GL/glew.h>
#include <vector>

namespace genesis {
namespace Constants {
// clang-format off
inline const std::vector<GLfloat> square = {
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f
};
// clang-format on
inline const std::vector<GLint> squareIndices = {0, 1, 3, 3, 1, 2};

constexpr int MAX_OVERWORLD_HEIGHT = 32;
constexpr int MAX_UNDERGROUND_HEIGHT = 32;
constexpr int FLAT_COMPENSATION_FACTOR = 12;

} // namespace Constants
} // namespace genesis
