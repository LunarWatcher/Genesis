#include "TextureAtlas.hpp"
#include "genesis/rendering/Constants.hpp"
#include "spdlog/spdlog.h"

namespace genesis {

TextureAtlas::TextureAtlas(const std::string& sourceFile)
        : Texture(sourceFile, 64, 64),
        atlasUnits(width / atlasTileWidth) {
    // temporary map metadata. This will eventually need to be outsourced somewhere else
    std::map<int, std::string> temporaryMetadata {
        {0, "genesis:grass"},
        {1, "genesis:stone"},
        {12 * 16, "genesis:colonist_a"}
    };

    for (auto& [tilePos, tileIdentifier] : temporaryMetadata) {
        int xCoords = tilePos % atlasUnits, yCoords = std::floor(tilePos / (double) atlasUnits);

        auto uv = this->generateFromPosition(xCoords, yCoords);
        models[tileIdentifier] = {
            tilePos,
            uv,
            std::make_shared<Model>(
                genesis::Constants::square,
                [&](Model* ptr) {
                    ptr->bindIndexBuffer(genesis::Constants::squareIndices);
                    ptr->createOrSubdataVBO(1, 2, uv);
                }
            )
        };

    }
}

} // namespace genesis
