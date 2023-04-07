#pragma once

#include "Tile.hpp"
#include "genesis/rendering/Entity.hpp"

#include <map>
#include <string>
#include <vector>

namespace genesis {

struct LayerTile {
    std::shared_ptr<Tile> floor;
    std::shared_ptr<Tile> block;
};

class ZLayer : public Entity {
public: // typedefs {{{
    /**
     * Outer vector: x
     * Inner vector: y
     *
     */
    using FloorMap = std::vector<std::vector<LayerTile>>;

    enum TileType {
        FLOOR,
        BLOCK
    };
// }}}
private:
    void regenerateVertices();
    bool dirty = false;

    FloorMap layer;

public:
    const int zLevel;
    
    ZLayer(int zLevel, int width, int height);

    void render() override;

    void set(std::shared_ptr<Tile>);

    friend class WorldGenerator;
};

}
