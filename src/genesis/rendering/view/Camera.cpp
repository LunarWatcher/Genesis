#include "Camera.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include <iostream>

namespace genesis {

Camera::Camera() {
    Renderer::getInstance().getInputManager()->registerKeyCallback(GLFW_KEY_W, // Map W
            0, // no modifiers
            [this](InputManager&, int action) {
                if (action != 0)
                    this->position.y += 10.0 * Renderer::getInstance().getDelta();
            });
    Renderer::getInstance().getInputManager()->registerKeyCallback(GLFW_KEY_A, 0, [this](InputManager&, int action) {
        if (action != 0)
            this->position.x -= 10.0 * Renderer::getInstance().getDelta();
    });
    Renderer::getInstance().getInputManager()->registerKeyCallback(GLFW_KEY_S, 0, [this](InputManager&, int action) {
        if (action != 0)
            this->position.y -= 10.0 * Renderer::getInstance().getDelta();
    });
    Renderer::getInstance().getInputManager()->registerKeyCallback(GLFW_KEY_D, 0, [this](InputManager&, int action) {
        if (action != 0)
            this->position.x += 10.0 * Renderer::getInstance().getDelta();
    });
}

void Camera::applyCamera(DefaultShader& shader) {
    regenerateCameraMatrix();
    shader.loadViewMatrix(this->matrix);
}

void Camera::regenerateCameraMatrix() {
    this->matrix =
            glm::lookAt(this->position, glm::vec3{this->position.x, this->position.y, 0}, glm::vec3{0.0f, 1.0f, 0.0f});
}

} // namespace genesis