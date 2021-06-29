#pragma once

namespace genesis {

class Rectangle;

/**
 * Abstract shared class for various colliders
 * The only current Collider is a Rectangle collider
 */
class Collider {
public:
    virtual ~Collider() = default;

    virtual bool collidesWith(const Rectangle& other) = 0;
};

}
