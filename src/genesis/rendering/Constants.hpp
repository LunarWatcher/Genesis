#pragma once

#include <GL/glew.h>
#include <vector>

namespace genesis {
namespace Constants {

inline std::vector<GLfloat> square = {0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f};
inline std::vector<GLint> squareIndices = {0, 1, 3, 3, 1, 2};

} // namespace Constants
} // namespace genesis
