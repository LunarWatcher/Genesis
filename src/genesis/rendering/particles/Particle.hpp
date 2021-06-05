#include "genesis/rendering/Renderable.hpp"

namespace genesis {

class Particle : public Renderable {
private:
    glm::vec2 position, velocity;
    glm::vec4 color;
    float aliveFor;

public:
    Particle() : position(0.0), velocity(0.0), color(1.0), aliveFor(0.0) {}

    void render() override;
};

} // namespace genesis
