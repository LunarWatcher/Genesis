#include "Camera.hpp"
#include "genesis/core/WorldController.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include <iostream>

namespace genesis {

Camera::Camera(InputManager& input) : inputManager(input) {
    inputManager.registerKeyCallback(GLFW_KEY_W, // Map W
            0, // no modifiers
            [this](InputManager&, int action) {
                if (action != 0)
                    this->position.y += 2.0 * WorldController::getWorld()->getDelta();
            });
    inputManager.registerKeyCallback(GLFW_KEY_A, 0, [this](InputManager&, int action) {
        if (action != 0)
            this->position.x -= 2.0 * WorldController::getWorld()->getDelta();
    });
    inputManager.registerKeyCallback(GLFW_KEY_S, 0, [this](InputManager&, int action) {
        if (action != 0)
            this->position.y -= 2.0 * WorldController::getWorld()->getDelta();
    });
    inputManager.registerKeyCallback(GLFW_KEY_D, 0, [this](InputManager&, int action) {
        if (action != 0)
            this->position.x += 2.0 * WorldController::getWorld()->getDelta();
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
