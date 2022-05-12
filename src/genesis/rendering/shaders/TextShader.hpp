#pragma once

#include "genesis/rendering/Shader.hpp"

#include "glm/glm.hpp"

namespace genesis {

class TextShader : public Shader {
protected:
    GLint textColor, //
        orthoMatrix,
        transform;

public:
    TextShader();
    virtual ~TextShader() = default;

    void loadTextColor(const glm::vec4& mVec);
    void loadOrthoMatrix(const glm::mat4& matrix);
    void loadTransMatrix(const glm::mat4& matrix) override;
};

} // namespace genesis
