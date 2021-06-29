#pragma once

#include "genesis/rendering/Entity.hpp"
#include "genesis/rendering/Renderable.hpp"
#include "Collider.hpp"

#include <memory>
#include <vector>

namespace genesis {

class PhysicsController {
protected:
    // TODO: quadtree or something to boost performance
    std::vector<std::shared_ptr<Entity>> entities;

public:

    // I guess we could use this for something
    virtual void tick() = 0;

};

}
