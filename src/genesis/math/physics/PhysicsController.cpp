#include "PhysicsController.hpp"
#include "genesis/math/physics/Rectangle.hpp"

namespace genesis {

bool PhysicsController::hasCollision(double x, double y) {
    // we make a pseudo-collider for the cursor
    std::shared_ptr<Collider> collider = std::make_shared<Rectangle>(x, y, 1, 1);
}

bool PhysicsController::hasCollision(std::shared_ptr<Collider> collider) {

    // This is where a quadtree optimization would be useful.
    for (auto& entity : entities) {
        auto& collider = entity->getCollider();
        // if the entity has a collider
        if (collider) {

        }
    }
}

}
