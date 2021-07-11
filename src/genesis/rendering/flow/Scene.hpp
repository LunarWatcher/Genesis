#include "genesis/math/physics/PhysicsController.hpp"
namespace genesis {

// Scenes are physics controllers. Brilliant, innit?
class Scene : public PhysicsController {
public:
    // Scenes are renderable and tickable
    // Ticking is also inherited from the PhysicsController
    void tick() override;
    void render();
};

}
