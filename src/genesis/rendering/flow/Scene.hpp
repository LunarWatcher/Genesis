#pragma once

#include "genesis/math/physics/PhysicsController.hpp"

namespace genesis {

class Scene {
protected:
    bool _isActive;
public:
    virtual ~Scene() = default;

    virtual void tick() = 0;
    virtual void render() = 0;

    // Lifecycle
    virtual void onPause() {}
    virtual void onDestroy() {}

    bool isActive() { return _isActive; }
    void setActive(bool active) { _isActive = active; }
};

}
