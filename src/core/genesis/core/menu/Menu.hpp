#include "genesis/math/physics/PhysicsController.hpp"
#include "genesis/rendering/flow/Scene.hpp"

#include "genesis/rendering/Renderable.hpp"
#include "genesis/world/EntityController.hpp"

namespace genesis {

// This is stupid design. Fix
class MenuController : public EntityController {
public:
    static constexpr long long BTN_PLAY = 0;

    MenuController();
    void tick() override;

    bool hasCollision(const std::shared_ptr<Rectangle>& collider) override;
};

class MenuScene : public Scene, public EntityController {
private:
    int selectedPosition = 0;

    std::vector<std::shared_ptr<EntityController>> entityControllers;
public:
    MenuScene();

    void render() override;
    void tick() override;

    const std::vector<std::shared_ptr<EntityController>>& getEntityControllers() override;

};

}
