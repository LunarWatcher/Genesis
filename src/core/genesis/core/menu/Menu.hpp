#include "genesis/math/physics/PhysicsController.hpp"
#include "genesis/rendering/flow/Scene.hpp"

#include "genesis/rendering/Renderable.hpp"
#include "genesis/world/EntityController.hpp"

namespace genesis {

class MenuScene : public Scene {
private:
    static constexpr long long BTN_PLAY = 0;

    std::vector<std::shared_ptr<Entity>> uiEntities;
public:
    MenuScene();

    void render() override;
    void tick() override;

    bool checkMouseCollision(const glm::vec2& rawCoords, const glm::vec3& /*projectedCoords*/) override;

};

}
