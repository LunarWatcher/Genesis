#pragma once

#include "genesis/conf/Settings.hpp"
#include "genesis/math/physics/Rectangle.hpp"
#include "genesis/rendering/Renderer.hpp"

namespace genesis {

namespace Ray {

glm::vec2 normalizeScreenCoords(double x, double y) {
    return {
        (2.0 * x) / Settings::instance->getInt("height") - 1.0,
        1.0 - (2.0 * y) / Settings::instance->getInt("height")
    };
}

std::shared_ptr<Entity> doesIntersect(const glm::vec2& normalizedScreenCoords) {
    Renderer& renderer = Renderer::getInstance();

    glm::vec4 rayClip(normalizedScreenCoords, -1.0, 1.0);

    auto& stack = renderer.getActiveSceneStack();

    for (auto& scene : stack) {
        //glm::vec4 eyeRay = glm::inverse(scene->)
        scene.get();
    }

    return nullptr;
}

}

}
