#include "Tile.hpp"

namespace genesis {

Tile::Tile(int atlasID, const std::string& tileID, bool isTextureSolid,
           bool isObjectSolid, int lightEmission,
           int blastResistance,
           int miningResistance) : atlasID(atlasID),
        tileID(tileID), isTextureSolid(isTextureSolid),
        isObjectSolid(isObjectSolid),
        lightEmission(lightEmission),
        blastResistance(blastResistance),
        miningResistance(miningResistance) {
}

}
