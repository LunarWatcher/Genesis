#pragma once

#include "genesis/core/metadata/TileMetadata.hpp"
#include <memory>
#include <string>

namespace genesis {

/**
 * Base class for all the tile objects.
 */
class Tile {
public:
    // The ID of the texture to use
    const unsigned int atlasID;

    std::shared_ptr<TileAttributes> tileAttribs;

    Tile(unsigned int atlasID, unsigned int lightEmission = 0);

    virtual void tick() {};

};

} // namespace genesis
