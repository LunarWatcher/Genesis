#pragma once

#include "genesis/rendering/Shader.hpp"

#include "glm/glm.hpp"

namespace genesis {

class TextShader : public Shader {
private:
    GLint textColor, //
        orthoMatrix;

public:
    TextShader();

    void loadTextColor(const glm::vec4& mVec);
    void loadOrthoMatrix(const glm::mat4& matrix);
};

} // namespace genesis
