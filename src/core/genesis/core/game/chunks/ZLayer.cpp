#include "ZLayer.hpp"
#include "genesis/core/game/chunks/ZLayer.hpp"

namespace genesis {

ZLayer::ZLayer(int zLevel, int width, int height) : zLevel(zLevel) {
    model->mode = GL_DYNAMIC_DRAW;
    model->createVAO();
    
    // This calculation is split up because it's annoying
    // Obvious: width * height = the number of tiles in a layer
    auto tilesInLayer = width * height;
    // Multiply by 2, because each layer consists of a floor and a tile.
    // Only one of them will actually be rendered, however, but that's fine. 
    // This is a performance decision.
    auto totalTilesInLayer = tilesInLayer * 2; // floor + blocks
    // Due to index coords being used, we're using 4 verties per tile.
    // Note that this is 2D, shit changes if this is upped  to 3D
    // Actually, if it's upgraded to 3D, other challenges are going to appear.
    // Particularly, several z-layers could be rendered at once, which means
    // a different culling system is needed.
    //
    // I consider this a problem for future me to have [fun](https://dwarffortresswiki.org/index.php/Fun) with
    auto totalVerticesInLayer = 4 * totalTilesInLayer;
    
    // Each vertex consists of three floats
    auto totalVertexFloats = 3 * totalVerticesInLayer;
    // Each UV coord and index coord consists of two floats
    auto totalUVCoords = 2 * totalVerticesInLayer;

    model->createVBO(0, 3, totalVertexFloats);
    model->createVBO(1, 2, totalUVCoords);
    model->bindIndexBuffer(totalUVCoords);

    regenerateVertices();
    glBindVertexArray(0);
}

void ZLayer::regenerateVertices() {
    glBindVertexArray(model->vaoID);
    
}

}
