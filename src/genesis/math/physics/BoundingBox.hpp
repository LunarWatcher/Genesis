#pragma once

namespace genesis  {

class BoundingBox {
private:
    virtual ~BoundingBox() = default;

    virtual bool collidesWith(BoundingBox& other);

    virtual int getWidth() = 0;
    virtual int getHeight() = 0;

    static bool collidesWith(BoundingBox& a, BoundingBox& b);
};

}
