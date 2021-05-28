#pragma once
#include "genesis/rendering/Shader.hpp"
#include "glm/common.hpp"
#include "glm/ext/matrix_float4x4.hpp"

namespace genesis {

/**
 * Renders textured blocks.
 */
class DefaultShader : public Shader {
private:
    // Matrix locations
    GLint transform, view, projection;

public:
    DefaultShader();

    void loadTransMatrix(const glm::mat4& matrix);
    void loadViewMatrix(glm::mat4 matrix);
    void loadProjectionMatrix(glm::mat4 matrix);
};

} // namespace genesis
