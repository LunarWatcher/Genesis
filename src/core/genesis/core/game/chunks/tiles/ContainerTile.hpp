#pragma once

#include "genesis/core/game/chunks/Tile.hpp"
#include "genesis/core/game/items/Inventory.hpp"
namespace genesis {

class ContainerTile : public Tile, public Inventory {
protected:

public:
    ContainerTile(int atlasID, const std::string& tileID, bool isTextureSolid,
                  bool isObjectSolid, int lightEmission,
                  int blastResistance,
                  int miningResistance,
                  unsigned int containerSize);

};

}
