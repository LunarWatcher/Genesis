#pragma once

#include "genesis/rendering/Renderable.hpp"
#include "genesis/rendering/Entity.hpp"
#include "Collider.hpp"

#include <memory>
#include <vector>

namespace genesis {

class PhysicsObject {
private:
    std::shared_ptr<Collider> collider;
    std::shared_ptr<Entity> entity;

public:
    PhysicsObject(std::shared_ptr<Collider> collider, std::shared_ptr<Entity> entity)
            : collider(collider), entity(entity) {
    }

    virtual void tick() = 0;
};

class PhysicsController : public Renderable {
private:
    std::vector<std::shared_ptr<PhysicsObject>> obj;
public:
    void render() override;


};

}
