#include "ParticleShader.hpp"

#include "genesis/rendering/Renderer.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace genesis {

ParticleShader::ParticleShader() : Shader("particle") {
    projectionMatrix = getUniformLocation("projectionMatrix");
    viewMatrix = getUniformLocation("viewMatrix");

    apply();
    loadProjectionMatrix(Renderer::getInstance().getCamera()->getPerspectiveMatrix());
    stop();
}

void ParticleShader::loadProjectionMatrix(const glm::mat4& matrix) {
    glUniformMatrix4fv(this->projectionMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ParticleShader::loadViewMatrix(const glm::mat4& matrix) {
    glUniformMatrix4fv(this->viewMatrix, 1, GL_FALSE, glm::value_ptr(matrix));
}

} // namespace genesis
