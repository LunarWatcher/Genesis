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

void DataHelper::registerTileGenerator(const std::string &tileID, std::shared_ptr<TileGenerator> generator) {
    if (generator == nullptr) {
        tileGenerators.erase(tileGenerators.find(tileID));
        return;
    }

    tileGenerators[tileID] = generator;
}

DataHelper* DataHelper::getInstance() {
    if (instance == nullptr) {
        instance = new DataHelper();
    }

    return instance;
}

}
