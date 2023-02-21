#pragma once

#include <memory>
#include <string>

namespace genesis {

/**
 * Base class for all the tile objects.
 * Contains methods for stuff:tm:, and default tile metadata.
 *
 * This class is additionally used for "dumb" environment tiles, such
 * as ground, walls, etc.
 */
class Tile {
public:
    // The ID of the texture to use
    const int atlasID;
    const std::string tileID;

    /**
     * Whether or not to render the tile underneath 
     * this tile
     */
    const bool isTextureSolid;

    /**
     * Whether or not the tile itself is considered solid
     */
    const bool isObjectSolid;

    const int lightEmission = 0;

    // Currently unused, and uses an undetermined value scheme.
    const int blastResistance = 0;

    // Currently unused, and uses an undetermined value scheme.
    const int miningResistance = 0;

    Tile(int atlasID, const std::string& tileID, bool isTextureSolid,
         bool isObjectSolid, int lightEmission,
         int blastResistance,
         int miningResistance);
    virtual ~Tile() = default;

    virtual void tick() {}
    virtual void destroy() {}
    virtual void onPlayerInteraction() {}

};

} // namespace genesis
