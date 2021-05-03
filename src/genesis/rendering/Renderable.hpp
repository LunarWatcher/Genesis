#pragma once

#include "genesis/rendering/shaders/DefaultShader.hpp"

namespace genesis {
class Renderable {
public:
    virtual ~Renderable() = default;
    virtual void render() = 0;
    // For future us
    // virtual void tick() = 0;
};

} // namespace genesis
