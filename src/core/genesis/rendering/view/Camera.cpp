#include "Camera.hpp"
#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_projection.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "spdlog/spdlog.h"
#include <iostream>
#include "genesis/conf/Settings.hpp"

namespace genesis {

Camera::Camera() {

    this->perspectiveMatrix = glm::perspective(glm::radians(FOV), 16.0f / 9.0f, NEAR_PLANE, FAR_PLANE);
    this->orthoMatrix = glm::ortho(0.0f, (float) Settings::instance->getInt("width"),
                                   0.0f, (float) Settings::instance->getInt("height"));

}

void Camera::regenerateCameraMatrix() {
    this->matrix
        = glm::lookAt(this->position,
                      glm::vec3{this->position.x, this->position.y, 0},
                      glm::vec3{0.0f, 1.0f, 0.0f});
}

void Camera::setYLayer(int newLayer) {
    // Possibly not super stonks for future use, but fuck it. Worked for minecraft, why not for me?
    if (newLayer < 1 || newLayer >= Constants::Chunks::CHUNK_HEIGHT) {
        // Throw?
        return;
    }
    this->activeYLayer = newLayer;
}

} // namespace genesis
