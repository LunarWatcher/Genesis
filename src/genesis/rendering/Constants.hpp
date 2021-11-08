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

// TODO: create a cache of possible cube indices based on which sides are free.

inline const std::vector<GLint> fullCubeIndices = {
    // Front
    0, 1, 3,
    3, 1, 2,
    // Back
    4, 5, 7,
    7, 5, 6,
    // Top
    0, 3, 4,
    7, 4, 3,
    // Bottom
    5, 2, 1,
    5, 6, 2,
    // Right
    7, 3, 2,
    6, 7, 2,
    // left
    0, 4, 5,
    5, 1, 0,

};

// I'm not convinced this is the best way to go about this.
constexpr int MAX_OVERWORLD_HEIGHT = 32;
constexpr int MAX_UNDERGROUND_HEIGHT = 32;
constexpr int FLAT_COMPENSATION_FACTOR = 12;

} // namespace Constants
} // namespace genesis
