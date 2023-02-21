#include "TileGenerator.hpp"
#include "genesis/rendering/Renderer.hpp"

namespace genesis {

TileGenerator::TileGenerator(const std::string& tileID, bool isTextureSolid, bool isObjectSolid, int lightEmission,
                             int blastResistance, int miningResistance)
    : atlasID(Renderer::getInstance().getTexturePack()->getTextureMetadata(tileID).tileId),
    tileID(tileID),
    isTextureSolid(isTextureSolid),
    isObjectSolid(isObjectSolid),
    lightEmission(lightEmission),
    blastResistance(blastResistance),
    miningResistance(miningResistance)
{

}

} // namespace genesis
