#include "ZLayer.hpp"

namespace genesis {

ZLayer::ZLayer(int zLevel) : zLevel(zLevel) {
    model->mode = GL_DYNAMIC_DRAW;
    model->createVAO();
    
}

}
