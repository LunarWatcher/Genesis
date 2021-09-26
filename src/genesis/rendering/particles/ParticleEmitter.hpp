#pragma once

#include "genesis/rendering/Model.hpp"
namespace genesis {

struct Particle {
    glm::vec3 position;
    glm::vec3 velocity;
    float scale;
};

class ParticleEmitter : public Model {
private:
    std::vector<Particle> particles;

public:
    ParticleEmitter();

    virtual void render() override;
};

} // namespace genesis
