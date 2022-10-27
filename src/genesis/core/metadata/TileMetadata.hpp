#pragma once

#include <map>
#include <any>
#include <string>
#include <functional>
#include <memory>

#define TA std::make_shared<TileAttributes> 

namespace genesis {

class Tile;

namespace TileGen {

std::shared_ptr<Tile> generateGenericTile();
std::shared_ptr<Tile> generateContainerTile();

}

typedef struct _TileAttributes {
    /**
     * Whether or not to render the tile underneath 
     * this tile
     */
    const bool isTextureSolid;

    /**
     * Whether or not the tile itself is considered solid
     */
    const bool isObjectSolid;

    std::function<std::shared_ptr<Tile>()> tileGen = TileGen::generateGenericTile;

    const int lightEmission = 0;

    // Currently unused, and uses an undetermined value scheme.
    const int blastResistance = 0;

    // Specific data
    std::map<std::string, std::any> specialData;

} TileAttributes;

static std::map<std::string, std::shared_ptr<TileAttributes>> tileMetadata = {
    {"genesis:grass", TA(true, true, TileGen::generateGenericTile, 0)},
    {"genesis:stone", TA(true, true, TileGen::generateGenericTile, 0)},
    {"genesis:caravan", TA(false, true, TileGen::generateContainerTile, 6)},
};

}
