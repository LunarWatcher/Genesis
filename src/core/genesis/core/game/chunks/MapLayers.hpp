#pragma once

#include <map>
#include <genesis/rendering/Entity.hpp>
#include <genesis/core/game/chunks/ZLayer.hpp>

namespace genesis {

/**
 * Utility wrapper containing the Z layers. Contains the main Z-layer renderer,
 * and is in charge of switching out the Z layers.
 *
 * This class essentially cuts down the vram requirement from up to a gigabyte for 64 layers
 * at 700x700 to a significantly lower amount.
 *
 * Not sure about the performance implication, but a large map might be up to 700x700 tiles
 */
class MapLayers : public Entity {
private:
    std::map<int, ZLayer> layers;
    bool dirty;
    int width, height;

    int layer = 0;

    void initModel();
    void regenerateLayerGraphics();
public:
    MapLayers(int width, int height);

    // TODO: this is probably going to have to act as the interface for the contained ZLayers to update specific tiles.
    // glSubData will at least increase the performance of on-layer updates.

    friend class WorldGenerator;
};

}
