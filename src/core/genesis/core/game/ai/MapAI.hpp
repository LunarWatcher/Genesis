#pragma once 

#include "genesis/core/game/ai/AI.hpp"

namespace genesis {

class MapAI : public AI {
public:
    void tick() override;
};

} /* genesis */ 
