#include "genesis/rendering/Entity.hpp"
#include "genesis/rendering/shaders/DefaultShader.hpp"
#include <map>
#include <memory>
#include <vector>

namespace genesis {

/**
 * Controls a system of entities, which can be considered to be equal to a team.
 */
class EntityController {
protected:
    std::vector<std::shared_ptr<Entity>> controlled;

public:
    virtual ~EntityController() = default;

    void render(DefaultShader& shader);
    virtual void tick() = 0;

    void addEntity(std::shared_ptr<Entity> entity);
};

} // namespace genesis
