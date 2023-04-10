#include "DefaultShader.hpp"

#include "GL/glew.h"

#include "genesis/Context.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "genesis/rendering/Renderer.hpp"

#include <iostream>

namespace genesis {

DefaultShader::DefaultShader() : DefaultShader("default") {}
DefaultShader::DefaultShader(const std::string& shader) : Shader(shader) {
    transform = this->getUniformLocation("transMatrix");
    view = this->getUniformLocation("viewMatrix");
    projection = this->getUniformLocation("projectionMatrix");

    apply();
    // we only need to load the projection matrix once
    loadProjectionMatrix(Context::getInstance().camera->getPerspectiveMatrix());
    stop();
}

void DefaultShader::loadProjectionMatrix(glm::mat4 matrix) {
    glUniformMatrix4fv(this->projection, 1, GL_FALSE, glm::value_ptr(matrix));
}

void DefaultShader::loadTransMatrix(const glm::mat4& matrix) {
    glUniformMatrix4fv(this->transform, 1, GL_FALSE, glm::value_ptr(matrix));
}

void DefaultShader::loadViewMatrix(glm::mat4 matrix) {
    glUniformMatrix4fv(this->view, 1, GL_FALSE, glm::value_ptr(matrix));
}

} // namespace genesis
