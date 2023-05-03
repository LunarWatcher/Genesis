#pragma once

#include "genesis/math/physics/Collider.hpp"
#include "glm/fwd.hpp"

namespace genesis {

class Rectangle : public Collider {
private:
    double x, y, z, //
        width, height;
public:
    Rectangle(double x, double y, double width, double height) : x(x), y(y), z(0), width(width), height(height) {}
    Rectangle(double x, double y, double z, double width, double height) : x(x), y(y), z(z), width(width), height(height) {}
    Rectangle(const glm::vec2& pos, const glm::vec2& dims) : x(pos.x), y(pos.y), z(0), width(dims.x), height(dims.y) {}

    bool collidesWith(const Rectangle& other, bool anyZ = false) override;

    void setDims(const double& width, const double& height) override;
    void update(const glm::vec3& pos) override;

    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }
    double getWidth() { return width; }
    double getHeight() { return height; }
};

}
