#pragma once

#include "genesis/math/physics/Rectangle.hpp"
#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Entity.hpp"
#include "genesis/rendering/Model.hpp"
namespace genesis {

class Primitive : public Entity {
public:
    /**
     * Square
     */
    Primitive(float x, float y, float z, float width, float height);

};

}
