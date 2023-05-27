#pragma once

#include "Tile.hpp"
#include "genesis/rendering/Entity.hpp"

#include <map>
#include <string>
#include <vector>

namespace genesis {

/**
 * Primitive object representing a tile at (x, y), defining both the floor and block tile.
 * To represent an empty floor and/or block, nullptr is used.
 */
struct LayerTile {
    std::shared_ptr<Tile> floor;
    std::shared_ptr<Tile> block;
};

class ZLayer {
public: // typedefs {{{
    /**
     * Outer vector: x
     * Inner vector: y
     *
     */
    using BlockMap = std::vector<std::vector<LayerTile>>;

    enum TileType {
        FLOOR,
        BLOCK
    };
// }}}
public:
    // Should not be written to externally, but fuuuuck making a getter
    BlockMap layer;

    const int zLevel;
    
    ZLayer(int zLevel, int worldWidth, int worldHeight);


    friend class WorldGenerator;
};

}
