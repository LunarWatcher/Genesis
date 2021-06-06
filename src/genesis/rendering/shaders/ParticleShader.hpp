#pragma once

#include "genesis/rendering/Shader.hpp"
#include "glm/ext/matrix_float4x4.hpp"

namespace genesis {

class ParticleShader : public Shader {
private:
    GLint projectionMatrix, //
        viewMatrix;

public:
    ParticleShader();

    void loadViewMatrix(const glm::mat4& matrix);
    void loadProjectionMatrix(const glm::mat4& matrix);
};

} // namespace genesis
