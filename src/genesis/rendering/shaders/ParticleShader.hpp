#include "genesis/rendering/Shader.hpp"

namespace genesis {

class ParticleShader : public Shader {
private:
    GLint projectionMatrix, //
        offset, //
        color;

public:
    ParticleShader() : Shader("shaders/particles") {
        projectionMatrix = getUniformLocation("projectionMatrix");
        offset = getUniformLocation("offset");
        color = getUniformLocation("color");
    }
};

} // namespace genesis
