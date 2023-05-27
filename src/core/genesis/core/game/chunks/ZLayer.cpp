#include "ZLayer.hpp"
#include "genesis/core/game/chunks/ZLayer.hpp"

namespace genesis {

ZLayer::ZLayer(int zLevel, int width, int height) : zLevel(zLevel) {
    layer.resize(width);
    for (auto& ySlice : layer) {
        ySlice.resize(height);
    }
}


}
