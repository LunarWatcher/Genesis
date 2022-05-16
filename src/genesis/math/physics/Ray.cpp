#include "Ray.hpp"

namespace genesis {


glm::vec2 Ray::normalizeScreenCoords(double x, double y) {
    return {
        (2.0 * x) / Settings::instance->getInt("width") - 1.0,
        1.0 - (2.0 * y) / Settings::instance->getInt("height")
    };
}

void Ray::traceClick(const glm::vec2& rawCoords, const glm::vec2& normalizedScreenCoords) {
    Renderer& renderer = Renderer::getInstance();

    auto& stack = renderer.getActiveSceneStack();

    for (auto& scene : stack) {
        if (!scene->usesOrtho()) {
            auto& viewMatrix = renderer.getCamera()->getViewMatrix();

            glm::vec4 rayClip(normalizedScreenCoords, -1.0, 1.0);
            glm::vec4 eyeRay = glm::inverse(renderer.getCamera()->getPerspectiveMatrix()) * rayClip;
            
            eyeRay.z = -1.0;
            eyeRay.w = 0.0;

            glm::vec3 worldRay = (glm::inverse(viewMatrix) * eyeRay);
            worldRay = glm::normalize(worldRay);

            spdlog::info("Base XYZ: {}, {}, {}", worldRay.x, worldRay.y, worldRay.z);

            for (int i = 0; i < 20; ++i) {
                // get a point on the ray
                glm::vec3 coords = renderer.getCamera()->getPosition() + ((float) i) * worldRay;
                spdlog::info("XYZ: {}, {}, {}", coords.x, coords.y, coords.z);

                for (auto& controller : scene->getEntityControllers()) {
                    if (controller->hasCollision(coords)) {
                        spdlog::info("Match");
                        return;
                    }
                }
                if (coords.z <= 0) {
                    spdlog::info("Terminating");
                    break;
                }
            }

        } else {
            for (auto& controller : scene->getEntityControllers()) {
                if (controller->hasCollision(rawCoords)) {
                    spdlog::info("Match");
                    return;
                }
            }
        }
        scene.get();
    }

}

}
