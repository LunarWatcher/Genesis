#pragma once

#include "genesis/rendering/Renderer.hpp"

namespace genesis {

class GameRenderer : public Renderer {
public:
    void tick();
    void render();
};

}
