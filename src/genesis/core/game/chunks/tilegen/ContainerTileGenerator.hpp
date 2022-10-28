#pragma once

#include "genesis/core/game/chunks/TileGenerator.hpp"
namespace genesis {

class ContainerTileGenerator : public TileGenerator {
protected:
    unsigned int containerSize;
public:
    ContainerTileGenerator(const std::string& tileID,
                           unsigned int containerSize,
                           bool isObjectSolid,
                           int lightEmission, 
                           int blastResistance,
                           int miningResistance);

    virtual std::shared_ptr<Tile> createTile() override;
};

}
