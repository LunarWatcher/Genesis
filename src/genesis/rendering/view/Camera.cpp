#include "Camera.hpp"
#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_projection.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include <iostream>

namespace genesis {

Camera::Camera() {

    this->perspectiveMatrix = glm::perspective(glm::radians(FOV), 16.0f / 9.0f, NEAR_PLANE, FAR_PLANE);
    this->orthoMatrix = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);

    auto inputManager = Renderer::getInstance().getInputManager();
    inputManager->registerKeyCallback(GLFW_KEY_W, // Map W
        0, // no modifiers
        [this](InputManager&, int action) {
            if (action != 0)
                this->position.y += 10.0 * Renderer::getInstance().getDelta();
            return false;
        });
    inputManager->registerKeyCallback(GLFW_KEY_A, 0, [this](InputManager&, int action) {
        if (action != 0)
            this->position.x -= 10.0 * Renderer::getInstance().getDelta();
        return false;
    });
    inputManager->registerKeyCallback(GLFW_KEY_S, 0, [this](InputManager&, int action) {
        if (action != 0)
            this->position.y -= 10.0 * Renderer::getInstance().getDelta();
        return false;
    });
    inputManager->registerKeyCallback(GLFW_KEY_D, 0, [this](InputManager&, int action) {
        if (action != 0)
            this->position.x += 10.0 * Renderer::getInstance().getDelta();
        return false;
    });
    /*
    // This changes which map level is currently active.
    // This code is not gonna be used until I figure out perlin, so I'm commenting it out.
    // I'd like to get the game going, not spend hours and hours on figuring out noise
    // this early. At least give me a chance to work on some AI first :dontfeelsoblob:
    inputManager->registerKeyCallback(GLFW_KEY_K, 0, [this](InputManager&, int action) {
        if (action == 1) {
            this->activeYLayer += 1;
            std::cout << this->activeYLayer << std::endl;
        }
        return true;
    });
    inputManager->registerKeyCallback(GLFW_KEY_J, 0, [this](InputManager&, int action) {
        if (action == 1) {
            this->activeYLayer -= 1;
        }
        return true;
    });
    */
}

void Camera::applyCamera(DefaultShader& shader) {
    regenerateCameraMatrix();
    shader.loadViewMatrix(this->matrix);
}

void Camera::regenerateCameraMatrix() {
    this->matrix
        = glm::lookAt(this->position, glm::vec3{this->position.x, this->position.y, 0}, glm::vec3{0.0f, 1.0f, 0.0f});
}

void Camera::setYLayer(int newLayer) {
    // TODO: Check which should be <= and which should be < given the environment
    // or >/>= or whatever
    if (newLayer <= Constants::MAX_UNDERGROUND_HEIGHT || newLayer >= Constants::MAX_OVERWORLD_HEIGHT)
        return;
    this->activeYLayer = newLayer;
}

glm::vec2 Camera::convertToWorld(double mouseX, double mouseY) {
    GLfloat z;

    GLfloat x = mouseX,
          y = 576 - mouseY;

    glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);

    return glm::vec2{
        glm::unProject(
            glm::vec3{
                x, y, z
            },
            this->matrix,
            this->perspectiveMatrix,
            glm::vec4{0, 0, 1024.0, 576.0}
        )
    };
}

} // namespace genesis
