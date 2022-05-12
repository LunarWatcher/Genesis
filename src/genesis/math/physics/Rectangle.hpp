#pragma once

#include "Collider.hpp"

namespace genesis {

class Rectangle : public Collider {
private:
    double x, y, z, //
        width, height;
public:
    Rectangle(double x, double y, double width, double height) : x(x), y(y), z(0), width(width), height(height) {}
    Rectangle(double x, double y, double z, double width, double height) : x(x), y(y), z(z), width(width), height(height) {}

    bool collidesWith(const Rectangle& other, bool anyZ = false) override;

    void setDims(const double& width, const double& height) override;
    void update(const Entity& e) override;

    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }
    double getWidth() { return width; }
    double getHeight() { return height; }
};

}
