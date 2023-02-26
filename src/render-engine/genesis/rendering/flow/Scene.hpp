#pragma once

#include "genesis/math/physics/PhysicsController.hpp"
#include "genesis/world/EntityController.hpp"
#include "genesis/input/InputProcessor.hpp"

namespace genesis {

class Scene : public PhysicsController, public InputProcessor {
protected:
    bool _isActive;
    bool _usesOrtho = false;

public:
    Scene() = default;
    Scene(bool _usesOrtho) : _usesOrtho(_usesOrtho) {}

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

    // Whether or not the scene is a UI scene
    // Returns true if the scene uses an orthographic projection,
    // false if it uses a perspective projection.
    virtual bool usesOrtho() {
        return _usesOrtho;
    }

};

}
