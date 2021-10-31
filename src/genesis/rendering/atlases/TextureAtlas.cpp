#include "TextureAtlas.hpp"
#include "genesis/rendering/Constants.hpp"
#include "spdlog/spdlog.h"

namespace genesis {
// clang-format off
#define STANDARD_ENTRY(tileType) \
    { WorldTile::tileType, \
      std::make_shared<Model>(genesis::Constants::square, \
    [&](Model* model) { \
        model->bindIndexBuffer(genesis::Constants::squareIndices); \
        model->createVBO(1, 2, generateFromPosition(decodeCoordinates((int) (WorldTile::tileType)))); \
    }) \
    }

TextureAtlas::TextureAtlas(const std::string& sourceFile)
        : Texture(sourceFile, 64, 64),
        atlasUnits(width / atlasTileWidth),
        models{
            STANDARD_ENTRY(GRASS),
            STANDARD_ENTRY(STONE),
            STANDARD_ENTRY(COLONIST_A)
        } {
}
// clang-format on

std::pair<int, int> TextureAtlas::decodeCoordinates(int offset) {
    return std::pair<int, int>{offset % atlasUnits, std::floor(offset / (double) atlasUnits)};
}

} // namespace genesis
