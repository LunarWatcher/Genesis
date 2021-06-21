#pragma once

namespace genesis {

class Rectangle;

class Collider {
public:
    virtual ~Collider() = default;

    virtual bool collidesWith(const Rectangle& other) = 0;
};

}
