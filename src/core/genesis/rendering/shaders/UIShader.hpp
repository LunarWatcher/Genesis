#pragma once

#include "genesis/rendering/Shader.hpp"

#include "glm/glm.hpp"

namespace genesis {

class UIShader : public Shader {
protected:
    GLint orthoMatrix;

public:
    UIShader();
    virtual ~UIShader() = default;

    void loadOrthoMatrix(const glm::mat4& matrix);
};

} // namespace genesis
