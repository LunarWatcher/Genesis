#pragma once

#include "Collider.hpp"

namespace genesis {

class Rectangle : public Collider {
private:
    int x, y, z, //
        width, height;
public:
    Rectangle(int x, int y, int width, int height) : x(x), y(y), z(0), width(width), height(height) {}
    Rectangle(int x, int y, int z, int width, int height) : x(x), y(y), z(z), width(width), height(height) {}

    bool collidesWith(const Rectangle& other, bool anyZ = false) override;

    void update(const Entity& e) override;
};

}
