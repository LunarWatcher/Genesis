#pragma once

#include "genesis/rendering/Renderable.hpp"

#include <memory>
#include <vector>

namespace genesis {

class PhysicsObject {
public:
    virtual void tick() = 0;
};

class PhysicsController : public Renderable {
private:
    std::vector<std::shared_ptr<PhysicsObject>> obj;
public:
    void render() override;


};

}
