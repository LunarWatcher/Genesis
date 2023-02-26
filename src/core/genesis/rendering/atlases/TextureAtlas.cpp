#include "TextureAtlas.hpp"
#include "genesis/rendering/Constants.hpp"
#include "spdlog/spdlog.h"
#include "genesis/rendering/Model.hpp"

namespace genesis {

TextureAtlas::TextureAtlas(const std::string& sourceFile)
        : Texture(sourceFile, 64, 64),
        atlasUnits(width / atlasTileWidth) {
    // temporary map metadata. This will eventually need to be outsourced somewhere else
    // Maybe. I don't know, modding is so far into the future that it's probably not worth
    // adding support for necessary bits until I need it.
    tileIDToString = {
        // The offsets are unnecessarily verbose for readability.
        // I can and probably should hide this in a method, but that's a job for future me
        {0 * 16 + 0, "genesis:grass"},
        {0 * 16 + 1, "genesis:stone"},

        {12 * 16 + 0, "genesis:red_fox"},

        {14 * 16 + 0, "genesis:caravan"},
    };

    for (auto& [tilePos, tileIdentifier] : tileIDToString) {
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
