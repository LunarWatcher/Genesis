#include "TextShader.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

namespace genesis {

TextShader::TextShader() : Shader("text") {
    textColor = this->getUniformLocation("textColor");
    orthoMatrix = this->getUniformLocation("orthoMatrix");

    apply();
    loadOrthoMatrix(Renderer::getInstance().getCamera()->getOrthoMatrix());
    stop();
}

void TextShader::loadTextColor(const glm::vec4& mVec) {
    glUniform4f(textColor, mVec.r, mVec.g, mVec.b, mVec.a);
}

void TextShader::loadOrthoMatrix(const glm::mat4& matrix) {
    glUniformMatrix4fv(this->orthoMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
}

} // namespace genesis
