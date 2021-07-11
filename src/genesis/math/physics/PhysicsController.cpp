#include "PhysicsController.hpp"
#include "genesis/math/physics/Rectangle.hpp"

namespace genesis {

bool PhysicsController::hasCollision(double x, double y) {
    // we make a pseudo-collider for the cursor
    std::shared_ptr<Rectangle> collider = std::make_shared<Rectangle>(x, y, 1, 1);
    return hasCollision(collider);
}

bool PhysicsController::hasCollision(std::shared_ptr<Rectangle> collider) {

    // This is where a quadtree optimization would be useful.
    for (auto& entity : entities) {
        auto entityCollider = entity->getCollider();
        // if the entity has a collider
        if (entityCollider != nullptr) {
            if (entityCollider->collidesWith(*collider, true)) return true;
        }
    }
    return false;
}

}
