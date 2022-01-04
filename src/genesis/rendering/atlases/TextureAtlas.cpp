#include "TextureAtlas.hpp"
#include "genesis/rendering/Constants.hpp"
#include "spdlog/spdlog.h"

namespace genesis {
// clang-format off
#define STANDARD_ENTRY(sheetCoords, tileID) \
    { tileID, { sheetCoords, \
      std::make_shared<Model>(genesis::Constants::square, \
    [&](Model* model) { \
        model->bindIndexBuffer(genesis::Constants::squareIndices); \
        model->createVBO(1, 2, generateFromPosition(decodeCoordinates(sheetCoords))); \
    }) \
    }}

TextureAtlas::TextureAtlas(const std::string& sourceFile)
        : Texture(sourceFile, 64, 64),
        atlasUnits(width / atlasTileWidth),
        // TODO: inject metadata to avoid hard-coding these values
        models{
            STANDARD_ENTRY(0, "genesis:grass"),
            STANDARD_ENTRY(1, "genesis:stone"),
            STANDARD_ENTRY(12 * 16, "genesis:colonist_a")
        } {
}
// clang-format on

std::pair<int, int> TextureAtlas::decodeCoordinates(const std::string& textureID) {
    // TODO: it's actually better to merge the UV coordinate generation into the model metadata.
    return decodeCoordinates(models.at(textureID).tileId);
}

std::pair<int, int> TextureAtlas::decodeCoordinates(int offset) {
    return std::pair<int, int>{offset % atlasUnits, std::floor(offset / (double) atlasUnits)};
}

} // namespace genesis
