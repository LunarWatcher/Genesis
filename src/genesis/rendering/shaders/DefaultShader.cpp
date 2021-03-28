#include "DefaultShader.hpp"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
namespace genesis {

DefaultShader::DefaultShader() : Shader("default") {
    transform = this->getUniformLocation("transMatrix");
    view = this->getUniformLocation("viewMatrix");
    projection = this->getUniformLocation("projectionMatrix");

    apply();
    // we only need to load the projection matrix once
    loadProjectionMatrix(glm::perspective(
        glm::radians(FOV),
        16.0f / 9.0f,
        NEAR_PLANE,
        FAR_PLANE
    ));
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

}
