#pragma once

#include "genesis/rendering/Entity.hpp"
#include "genesis/rendering/shaders/DefaultShader.hpp"
#include <map>
#include <memory>
#include <vector>

namespace genesis {

/**
 * Controls a system of entities, which can be considered to be equal to a team.
 */
class EntityController : public Renderable {
protected:
    std::vector<std::shared_ptr<Entity>> controlled;

public:
    virtual ~EntityController() = default;

    virtual void render() override;
    virtual void tick() = 0;

    void addEntity(std::shared_ptr<Entity> entity);
};

} // namespace genesis
