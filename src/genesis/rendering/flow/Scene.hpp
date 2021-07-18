#pragma once

#include "genesis/math/physics/PhysicsController.hpp"

namespace genesis {

class Scene {
protected:
    bool _isActive;
public:
    virtual void tick() = 0;
    virtual void render() = 0;

    bool isActive() { return _isActive; }
    void setActive(bool active) { _isActive = active; }
};

}
