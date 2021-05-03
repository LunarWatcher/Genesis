#pragma once

#include "EntityController.hpp"
#include <vector>

namespace genesis {

class PlayerCamp : public EntityController {
public:
    PlayerCamp() = default;

    void tick() override;
};

} // namespace genesis
