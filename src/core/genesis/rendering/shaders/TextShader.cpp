#include "TextShader.hpp"
#include "genesis/Context.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

namespace genesis {

TextShader::TextShader() : Shader("text") {
    textColor = this->getUniformLocation("textColor");
    backgroundColour = this->getUniformLocation("backgroundColour");
    orthoMatrix = this->getUniformLocation("orthoMatrix");

    apply();
    loadTextColor({0.0, 0.0, 0.0, 1.0});
    loadOrthoMatrix(Context::getInstance().camera->getOrthoMatrix());
    stop();
}

// This is stupid. This should be simplified
void TextShader::loadTextColor(const glm::vec4& mVec) {
    glUniform4fv(textColor, 1, &mVec[0]);
}

void TextShader::loadBackgroundColour(const glm::vec4& mVec) {
    glUniform4fv(backgroundColour, 1, &mVec[0]);
}

void TextShader::loadOrthoMatrix(const glm::mat4& matrix) {
    glUniformMatrix4fv(this->orthoMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
}

} // namespace genesis
