#pragma once

#include "genesis/rendering/Model.hpp"
namespace genesis {

struct Particle {
    glm::vec4 position;
    float scale;
};

class ParticleEmitter : public Model {
private:
    std::vector<Particle> particles;

public:
    ParticleEmitter();

    void render() override;
};

} // namespace genesis
