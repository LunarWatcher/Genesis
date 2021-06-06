#pragma once
#include "genesis/controls/InputManager.hpp"
#include "genesis/rendering/Shader.hpp"
#include "genesis/rendering/shaders/DefaultShader.hpp"
#include "glm/ext/vector_float3.hpp"
#include <memory>

namespace genesis {

class Camera {
public:
    static constexpr inline float FOV = 70.0f;
    static constexpr inline float NEAR_PLANE = 0.1f;
    static constexpr inline float FAR_PLANE = 1000.0f;

private:
    /**
     * Since we're sticking with 2D graphics, a single 3D vector is enough to contain the map.
     * Changing the up vector should affect camera rotation, but that's probably an unnecessary
     * feature.
     */
    glm::vec3 position = {1, 1, 5};
    glm::mat4 matrix;

    glm::mat4 orthoMatrix;
    glm::mat4 perspectiveMatrix;

    int activeYLayer = 0;

    void regenerateCameraMatrix();

public:
    Camera();
    void applyCamera(DefaultShader& shader);

    void setYLayer(int newLayer);

    int getActiveY() {
        return activeYLayer;
    }

    const glm::mat4 getViewMatrix() {
        return matrix;
    }

    const glm::mat4& getPerspectiveMatrix() {
        return perspectiveMatrix;
    }

    const glm::mat4& getOrthoMatrix() {
        return orthoMatrix;
    }
};

} // namespace genesis
