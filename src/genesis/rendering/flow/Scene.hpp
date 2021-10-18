#pragma once

#include "genesis/math/physics/PhysicsController.hpp"
#include "genesis/world/EntityController.hpp"

namespace genesis {

class Scene : public PhysicsController {
protected:
    bool _isActive;
public:
    virtual ~Scene() = default;

    virtual void render() = 0;

    virtual const std::vector<std::shared_ptr<EntityController>>& getEntityControllers() {
        static std::vector<std::shared_ptr<EntityController>> ref = {};
        return ref;
    }

    // Lifecycle
    virtual void onPause() {}
    virtual void onDestroy() {}
    virtual void onResume() {}

    bool isActive() const { return _isActive; }
    void setActive(bool active) { _isActive = active; }
};

}
