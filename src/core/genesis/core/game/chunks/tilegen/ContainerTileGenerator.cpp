#include "ContainerTileGenerator.hpp"
#include "genesis/core/game/chunks/tiles/ContainerTile.hpp"

namespace genesis {

ContainerTileGenerator::ContainerTileGenerator(const std::string& tileID,
                                               unsigned int containerSize,
                                               bool isObjectSolid,
                                               int lightEmission,
                                               int blastResistance, int miningResistance)
        : TileGenerator(tileID, false, isObjectSolid, lightEmission, blastResistance, miningResistance),
        containerSize(containerSize) {

}

std::shared_ptr<Tile> ContainerTileGenerator::createTile() {
    return std::make_shared<ContainerTile>(
        atlasID,
        tileID,
        isTextureSolid,
        isObjectSolid,
        lightEmission,
        blastResistance,
        miningResistance,
        containerSize
    );
}

} // namespace genesis
