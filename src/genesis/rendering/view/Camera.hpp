#pragma once
#include "genesis/controls/InputManager.hpp"
#include "genesis/rendering/Shader.hpp"
#include "genesis/rendering/shaders/DefaultShader.hpp"
#include "glm/ext/vector_float3.hpp"
#include <memory>

namespace genesis {

class Camera {
private:
    /**
     * Since we're sticking with 2D graphics, a single 3D vector is enough to contain the map.
     * Changing the up vector should affect camera rotation, but that's probably an unnecessary
     * feature.
     */
    glm::vec3 position = {1, 1, 5};
    glm::mat4 matrix;

    int activeYLayer = 0;

    void regenerateCameraMatrix();

public:
    Camera();
    void applyCamera(DefaultShader& shader);

    void setYLayer(int newLayer);
    int getActiveY() {
        return activeYLayer;
    }
};

} // namespace genesis
