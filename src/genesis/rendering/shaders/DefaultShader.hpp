#pragma once
#include "genesis/rendering/Shader.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/common.hpp"

namespace genesis {

/**
 * Renders textured blocks.
 */
class DefaultShader : public Shader {
private:
    static constexpr inline float FOV = 70.0f;
    static constexpr inline float NEAR_PLANE = 0.1f;
    static constexpr inline float FAR_PLANE = 1000.0f;
    // Matrix locations
    GLint transform, view, projection;
public:
    DefaultShader();

    void loadTransMatrix(const glm::mat4& matrix);
    void loadViewMatrix(glm::mat4 matrix);
    void loadProjectionMatrix(glm::mat4 matrix);
};

}
