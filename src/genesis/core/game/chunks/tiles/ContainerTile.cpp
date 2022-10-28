#include "ContainerTile.hpp"

namespace genesis {

ContainerTile::ContainerTile(int atlasID, const std::string& tileID, bool isTextureSolid,
           bool isObjectSolid, int lightEmission,
           int blastResistance,
           int miningResistance,
           unsigned int containerSize)
    : Tile(atlasID, tileID, isTextureSolid,
           isObjectSolid, lightEmission,
           blastResistance,
           miningResistance),
    Inventory(containerSize){
}

}
