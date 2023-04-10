#include "UIShader.hpp"
#include "genesis/Context.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

namespace genesis {

UIShader::UIShader() : Shader("ui") {
    orthoMatrix = this->getUniformLocation("orthoMatrix");

    apply();
    loadOrthoMatrix(Context::getInstance().camera->getOrthoMatrix());
    stop();
}

void UIShader::loadOrthoMatrix(const glm::mat4& matrix) {
    glUniformMatrix4fv(this->orthoMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
}

} // namespace genesis
