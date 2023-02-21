#include "genesis/core/game/chunks/TileGenerator.hpp"

namespace genesis {

class TerrainTileGenerator : public TileGenerator {
public:
    TerrainTileGenerator(const std::string& tileID,
                         int lightEmission, 
                         int blastResistance,
                         int miningResistance);

    virtual std::shared_ptr<Tile> createTile() override;
};

}
