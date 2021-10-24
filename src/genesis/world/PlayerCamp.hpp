#pragma once

#include "EntityController.hpp"
#include "genesis/math/physics/PhysicsController.hpp"
#include "genesis/rendering/Entity.hpp"

#include <vector>
#include <queue>

namespace genesis {

class PlayerCamp : public EntityController {
public:
    PlayerCamp() = default;

    void tick() override;
};

} // namespace genesis
