#pragma once

#include "genesis/core/game/chunks/Tile.hpp"
#include <memory>

namespace genesis {

class TileGenerator {
protected:
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
public:
    TileGenerator(const std::string& tileID, bool isTextureSolid,
         bool isObjectSolid, int lightEmission,
         int blastResistance,
         int miningResistance);

    virtual ~TileGenerator() = default;

    /**
     * Called when a new tile is created manually, such as when a tile is placed.
     */
    virtual std::shared_ptr<Tile> createTile() = 0;

    /**
     * Same as createTile() by default, but this is only ever called by worldgen.
     * Should be overridden by special tiles that do more than just create the tile.
     */
    virtual std::shared_ptr<Tile> generateTile() { return createTile(); };

    const std::string& getStringID() { return tileID; }
    const int& getAtlasID() { return atlasID; }
};

}
