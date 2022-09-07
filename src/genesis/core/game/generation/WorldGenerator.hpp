#pragma once

#include "genesis/core/game/World.hpp"

#include <string>

namespace genesis {

class WorldGenerator {
public:

    static std::shared_ptr<World> newWorld(
        int xChunks, int yChunks,
        const std::string& civName
    );
    
};

}
