#include "genesis/math/physics/PhysicsController.hpp"
#include "genesis/rendering/flow/Scene.hpp"

#include "genesis/rendering/Renderable.hpp"

namespace genesis {

class MenuScene : public Scene {
private:
    int selectedPosition = 0;

    std::vector<std::shared_ptr<Renderable>> models;
public:
    MenuScene();

    void render() override;
    void tick() override;
};

}
