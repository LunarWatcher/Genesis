#include "DataHelper.hpp"

#include "genesis/core/game/chunks/tilegen/TerrainTileGenerator.hpp"
#include "genesis/core/game/chunks/tilegen/ContainerTileGenerator.hpp"

#define TG(id, T, ...) {id, std::static_pointer_cast<TileGenerator>(std::make_shared<T>(id, __VA_ARGS__))}

namespace genesis {

DataHelper::DataHelper() {
    tileGenerators = {
        TG("genesis:grass", TerrainTileGenerator,
           0, 0, 0),
        TG("genesis:stone", TerrainTileGenerator,
           0, 0, 0),
        TG("genesis:caravan", ContainerTileGenerator,
           24,
           true,
           0, 0, 0
        ),
    };
}

DataHelper* DataHelper::getInstance() {
    if (instance == nullptr) {
        instance = new DataHelper();
    }

    return instance;
}

}
