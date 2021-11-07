#pragma once

#include <GL/glew.h>
#include <vector>

namespace genesis {
namespace Constants {

inline const std::vector<GLfloat> square = {
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f
};

inline const std::vector<GLint> squareIndices = {0, 1, 3, 3, 1, 2};

inline const std::vector<GLfloat> cube = {
    0.0, 0.0, 1.0,
    1.0, 0.0, 1.0,
    0.0, 1.0, 1.0,
    1.0, 1.0, 1.0,
    0.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
};

// TODO: create a cache of possible cube vertices based on which sides are free.
inline const std::vector<GLint> fullCubeVertices = {
    0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
};

// I'm not convinced this is the best way to go about this.
//constexpr int MAX_OVERWORLD_HEIGHT = 32;
//constexpr int MAX_UNDERGROUND_HEIGHT = 32;
//constexpr int FLAT_COMPENSATION_FACTOR = 12;

} // namespace Constants
} // namespace genesis
