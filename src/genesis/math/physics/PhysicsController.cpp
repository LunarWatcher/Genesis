#include "PhysicsController.hpp"
#include "genesis/math/physics/Collider.hpp"
#include "genesis/math/physics/Rectangle.hpp"

namespace genesis {

bool PhysicsController::hasCollision(const glm::vec2& coords) {
    // we make a pseudo-collider for the cursor
    std::shared_ptr<Rectangle> collider = std::make_shared<Rectangle>(coords.x, coords.y, 0, 0.001, 0.001);
    return hasCollision(collider);
}

bool PhysicsController::hasCollision(const std::shared_ptr<Rectangle>& collider) {
    // This is where a quadtree optimization would be useful.
    for (auto& entity : entities) {
        // if the entity has a collider
        if (entity->getCollider() != nullptr) {
            if (entity->getCollider()->collidesWith(*collider, true)) {
                return true;
            }
        }
    }
    return false;
}

}
