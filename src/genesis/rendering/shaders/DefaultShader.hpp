#pragma once
#include "genesis/rendering/Shader.hpp"

namespace genesis {

/**
 * Renders textured blocks.
 */
class DefaultShader : public Shader {
public:
    DefaultShader() : Shader("default") {
        
    }
};

}
