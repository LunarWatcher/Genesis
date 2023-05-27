#pragma once

#include "genesis/core/game/World.hpp"
#include "glm/glm.hpp"

#include <string>

namespace genesis {

class WorldGenerator {
private:
    static void generateCharacters(const glm::vec3& caravanPosition, std::shared_ptr<World> world, int count);
public:

    static std::shared_ptr<World> newWorld(
        int width, int height,
        const std::string& civName
    );
    
};

}
