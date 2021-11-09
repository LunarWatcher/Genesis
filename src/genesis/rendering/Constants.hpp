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
    // front vertices
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    // Back vertices
    0.0f, 1.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    1.0f, 0.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
};

inline const std::vector<GLint> fullCubeIndices = {
    // Front
    0, 1, 3,
    3, 1, 2,
    // Back
    4, 5, 7,
    7, 5, 6,
    // Top
    4, 0, 7,
    7, 0, 3,
    // Bottom
    1, 5, 2,
    2, 5, 6,
    // Right
    3, 2, 7,
    7, 2, 6,
    // left
    4, 5, 0,
    0, 5, 1
};

// I'm not convinced this is the best way to go about this.
constexpr int MAX_OVERWORLD_HEIGHT = 32;
constexpr int MAX_UNDERGROUND_HEIGHT = 32;
constexpr int FLAT_COMPENSATION_FACTOR = 12;

} // namespace Constants
} // namespace genesis
