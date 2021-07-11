#pragma once

#include "genesis/rendering/Entity.hpp"
#include "genesis/rendering/Renderable.hpp"
#include "Collider.hpp"

#include <memory>
#include <vector>

namespace genesis {

/**
 * PhysicsController is just a glorified way of saying that an AI controller is also a
 * thing that manages physics.
 *
 * The core logic is going to be implemented in the super class.
 */
class PhysicsController {
protected:
    // TODO: quadtree or something to boost performance
    std::vector<std::shared_ptr<Entity>> entities;

public:

    // I guess we could use this for something
    virtual void tick() = 0;

    bool hasCollision(double x, double y);
    bool hasCollision(std::shared_ptr<Collider> collider);
};

}
