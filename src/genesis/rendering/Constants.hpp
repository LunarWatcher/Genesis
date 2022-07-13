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

/**
 * As much as I wish this was simpler... it's not doable.
 * We need to render the same vertices as separate instances,
 * because otherwise, it fucks up the rendering of the side textures.
 *
 * Concretely, there's only two sides with vertex coords, and there's a mismatch
 * that results in a wildly wrong texture being applied on the sides.
 * The only way around this is fragmenting it; each cube is no longer a cube,
 * but six sides. The difference being that we can actually assign texture coords
 * in a sane way.
 *
 * Unfortunately requires 4*4 additional points for all sides that aren't
 * the bottom
 */
inline const std::vector<GLfloat> cube = {
    // front vertices
    0.0, 1.0, 0.0,
    0.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 1.0, 0.0,
    // Back vertices
    0.0, 1.0, -1.0,
    0.0, 0.0, -1.0,
    1.0, 0.0, -1.0,
    1.0, 1.0, -1.0,
    // Top
    0.0, 1.0, -1.0,
    0.0, 1.0, 0.0,
    1.0, 1.0, -1.0,
    1.0, 1.0, 0.0,
    // bottom
    0.0, 0.0, 0.0,
    0.0, 0.0, -1.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, -1.0,
    // right
    1.0, 1.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 1.0, -1.0,
    1.0, 0.0, -1.0,
    // left
    0.0, 1.0, -1.0,
    0.0, 0.0, -1.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 0.0,
};

inline const std::vector<GLint> fullCubeIndices = {
    // Front
    0, 1, 3,
    3, 1, 2,
    // Back
    4, 5, 7,
    7, 5, 6,
    // Top
    8, 9, 10,
    10, 9, 11,
    // Bottom
    12, 13, 14,
    14, 13, 15,
    // Right
    16, 17, 18,
    18, 17, 19,
    // left
    20, 21, 22,
    22, 21, 23,
};

// I'm not convinced this is the best way to go about this.
constexpr int MAX_OVERWORLD_HEIGHT = 32;
constexpr int MAX_UNDERGROUND_HEIGHT = 32;
constexpr int FLAT_COMPENSATION_FACTOR = 12;

namespace Chunks {
static constexpr int CHUNK_SIZE = 16;
static constexpr int CHUNK_HEIGHT = 64;
static constexpr int CHUNK_SEA_LEVEL = 20;


static constexpr int WORST_CASE_SIZE = Constants::Chunks::CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT // amount of cubes
                     * 24 // Multiplied by the number of vertices in a cube
                     / 8; // Divided by 1/2^3, which gives us the worst case rendering: alternating cubes on every layer.
                           // admittedly a bit higher, because we can simplify away certain vertices, but for V1
                           // when I have absolutely no clue what I'm doing... it's good enough.

}

} // namespace Constants
} // namespace genesis
