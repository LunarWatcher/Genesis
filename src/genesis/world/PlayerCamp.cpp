#include "PlayerCamp.hpp"
#include "genesis/rendering/Renderer.hpp"

#include <iostream>
#include <math.h>

namespace genesis {

void PlayerCamp::tick() {
    for (auto& entity : this->entities) {
        entity->modify([entity]() {
            auto& pos = entity->getPosition();
            pos.x += 0.8 * Renderer::getInstance().getDelta();

            pos.y = sin(pos.x);

            return true;
        });
        entity->tick();
    }
}

} // namespace genesis
