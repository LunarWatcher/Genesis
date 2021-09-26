#pragma once

#include "genesis/rendering/Entity.hpp"
namespace genesis {

struct Particle {
    glm::vec3 position;
    glm::vec3 velocity;
    float scale;
};

class ParticleEmitter : public Entity {
private:
    std::vector<Particle> particles;

public:
    ParticleEmitter();

    virtual void render() override;
};

} // namespace genesis
