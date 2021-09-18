#include "genesis/math/physics/PhysicsController.hpp"
#include "genesis/rendering/flow/Scene.hpp"

namespace genesis {

class MenuScene : public Scene {
private:
    int selectedPosition = 0;

    std::vector<std::shared_ptr<Model>> models;
public:
    MenuScene();

    void render() override;
    void tick() override;
};

}
