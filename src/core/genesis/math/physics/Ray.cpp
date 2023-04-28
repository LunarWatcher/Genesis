#include "Ray.hpp"
#include "genesis/Context.hpp"

namespace genesis {


glm::vec2 Ray::normalizeScreenCoords(double x, double y) {
    return {
        (2.0 * x) / Settings::instance->getInt("width") - 1.0,
        1.0 - (2.0 * y) / Settings::instance->getInt("height")
    };
}

bool Ray::traceClick(const glm::vec2& rawCoords, const glm::vec2& normalizedScreenCoords) {
    auto cam = Context::getInstance().camera;

    auto& stack = Context::getInstance().renderer->getActiveSceneStack();

    for (auto& scene : stack) {
        if (!scene->usesOrtho()) {
            auto& viewMatrix = cam->getViewMatrix();

            glm::vec4 rayClip(normalizedScreenCoords, -1.0, 1.0);
            glm::vec4 eyeRay = glm::inverse(cam->getPerspectiveMatrix()) * rayClip;
            
            eyeRay.z = -1.0;
            eyeRay.w = 0.0;

            glm::vec3 worldRay = (glm::inverse(viewMatrix) * eyeRay);
            worldRay = glm::normalize(worldRay);

            // this is deceptively simple, but not in any way flexible.
            // We assume raycasting only is performed for our world, where the z is discrete anyway, and it's mostly tiled.
            // We just need to find the difference:
            // This is a real nasty hack taking advantage of how this particular world works.
            // This isn't true raycasting per se, but it's good enough for converting to world coordinates.
            //
            // The hack here is that z = 0 is representative for the current layer. There's only one layer rendered at a time,
            // so we can use:
            //   camPos.z + n * worldRay.z = ground.z = 0
            //   n * worldRay.z = -camPos.z => n = -camPos.z / worldRay.z
            //
            // If you're here to copy code for your own game (at least give me a footnote in the acknowledgements if you do),
            // this is a nasty hack based on an assumption about this spcific game.
            // Because everything is at z = 0, the above equation works.
            // In other cases, you have to determine the z manually with the raycasting process. Depending on the game, the math
            // for that ranges from trivial elementary school math to shit there's several papers about.
            //
            // Mind the minus, though! Dropping it breaks the math.
            double dist = -cam->getPosition().z / worldRay.z;

            glm::vec3 coords = cam->getPosition() + ((float) dist) * worldRay;

            for (auto& controller : scene->getEntityControllers()) {
                if (controller->hasCollision(coords)) {
                    //spdlog::info("Match");
                    return true;
                }
            }

        } else {
            // Ortho viewports use the raw coordinates, i.e. pixel coords rather than OpenGL coords.
            // No transformation needed because it's all on one y-level, so shove it straight through
            // the collision checking system
            for (auto& controller : scene->getEntityControllers()) {
                if (controller->hasCollision(rawCoords)) {
                    //spdlog::info("Match");
                    return true;
                }
            }
        }
    }
    return false;
}

}
