#pragma once

#include "EntityController.hpp"
#include "genesis/math/physics/PhysicsController.hpp"
#include <vector>
#include "genesis/rendering/Entity.hpp"

namespace genesis {

class PlayerCamp : public EntityController {
public:
    PlayerCamp() = default;

    void tick() override;
};

} // namespace genesis
