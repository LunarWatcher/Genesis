#pragma once

#include "genesis/conf/Settings.hpp"
#include "genesis/math/physics/Rectangle.hpp"
#include "genesis/rendering/Renderer.hpp"

namespace genesis {

namespace Ray {

// TODO: move to source file
inline glm::vec2 normalizeScreenCoords(double x, double y) {
    return {
        (2.0 * x) / Settings::instance->getInt("height") - 1.0,
        1.0 - (2.0 * y) / Settings::instance->getInt("height")
    };
}

inline void traceClick(const glm::vec2& rawCoords, const glm::vec2& normalizedScreenCoords) {
    Renderer& renderer = Renderer::getInstance();

    auto& stack = renderer.getActiveSceneStack();

    for (auto& scene : stack) {
        if (!scene->usesOrtho()) {

            glm::vec4 rayClip(normalizedScreenCoords, -1.0, 1.0);
            glm::vec4 eyeRay = glm::inverse(renderer.getCamera()->getPerspectiveMatrix()) * rayClip;
            eyeRay.z = -1.0;
            eyeRay.w = 0.0;

            glm::vec3 worldRay = (glm::inverse(renderer.getCamera()->getViewMatrix()) * eyeRay);
            worldRay = glm::normalize(worldRay);

            spdlog::info("XYZ: {}, {}, {}", worldRay.x, worldRay.y, worldRay.z);
        } else {
            for (auto& controller : scene->getEntityControllers()) {
                if (controller->hasCollision(rawCoords)) {
                    spdlog::info("Match");
                    goto outer;
                }
            }
        }
        scene.get();
    }

outer:;
}

}

}
