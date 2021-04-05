#include "Camera.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include <iostream>

namespace genesis {

Camera::Camera(InputManager& input) : inputManager(input) {
    inputManager.registerKeyCallback(
        GLFW_KEY_A, // Map A
        0, // no modifiers
        [](InputManager&, int action) {
            std::cout << action << std::endl;
        }
    );
}

void Camera::applyCamera(DefaultShader& shader) {
    regenerateCameraMatrix();
    shader.loadViewMatrix(this->matrix);
}

void Camera::regenerateCameraMatrix() {
    this->matrix = glm::lookAt(this->position, glm::vec3{this->position.x, this->position.y, 0}, glm::vec3{0.0f, 1.0f, 0.0f});
}

}
