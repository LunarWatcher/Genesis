#include "TerrainTileGenerator.hpp"

namespace genesis {

TerrainTileGenerator::TerrainTileGenerator(
    const std::string& tileID,
    int lightEmission, 
    int blastResistance,
    int miningResistance)
    : TileGenerator(tileID, true, true,
                    lightEmission,
                    blastResistance,
                    miningResistance) {

}

std::shared_ptr<Tile> TerrainTileGenerator::createTile() {

    return std::make_shared<Tile>(
        atlasID,
        tileID,
        isTextureSolid,
        isObjectSolid,
        lightEmission,
        blastResistance,
        miningResistance
    );
}

}
