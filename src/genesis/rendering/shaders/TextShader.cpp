#include "TextShader.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

namespace genesis {

TextShader::TextShader() : Shader("text") {
    textColor = this->getUniformLocation("textColor");
    orthoMatrix = this->getUniformLocation("orthoMatrix");
    transform = this->getUniformLocation("transMatrix");

    apply();
    loadTextColor({0.0, 0.0, 0.0, 1.0});
    loadOrthoMatrix(Renderer::getInstance().getCamera()->getOrthoMatrix());
    stop();
}

void TextShader::loadTextColor(const glm::vec4& mVec) {
    glUniform4fv(textColor, 1, &mVec[0]);
}

void TextShader::loadOrthoMatrix(const glm::mat4& matrix) {
    glUniformMatrix4fv(this->orthoMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
}

void TextShader::loadTransMatrix(const glm::mat4& matrix) {
    glUniformMatrix4fv(this->transform, 1, GL_FALSE, glm::value_ptr(matrix));
}

} // namespace genesis
