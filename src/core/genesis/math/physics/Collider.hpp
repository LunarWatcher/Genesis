#pragma once

namespace genesis {

class Rectangle;
class Entity;

/**
 * Abstract shared class for various colliders
 * The only current Collider is a Rectangle collider
 */
class Collider {
public:
    virtual ~Collider() = default;

    virtual bool collidesWith(const Rectangle& other, bool anyZ = false) = 0;

    virtual void setDims(const double& w, const double& y) = 0;
    virtual void update(const Entity& e) = 0;
};

}
