#pragma once

#include "genesis/math/physics/PhysicsController.hpp"

namespace genesis {

class Scene : public PhysicsController {
protected:
    bool _isActive;
public:
    virtual ~Scene() = default;

    virtual void render() = 0;

    // Lifecycle
    virtual void onPause() {}
    virtual void onDestroy() {}
    virtual void onResume() {}

    bool isActive() const { return _isActive; }
    void setActive(bool active) { _isActive = active; }
};

}
