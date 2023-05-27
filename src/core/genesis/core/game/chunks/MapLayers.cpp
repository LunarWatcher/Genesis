#include "MapLayers.hpp"
#include "genesis/Context.hpp"
#include "genesis/rendering/Constants.hpp"

namespace genesis {

MapLayers::MapLayers(int width, int height) : Entity(std::make_shared<Model>(), {0, 0, 0}), width(width), height(height) {
    initModel();
}

void MapLayers::initModel() {
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

    // Each UV coord and index coord consists of two floats
    auto totalUVCoords = 2 * totalVerticesInLayer;

    model->bindIndexBuffer(totalUVCoords);

    std::vector<GLfloat> initVertices;
    std::vector<GLint> indices;

    // TODO: rename this, ffs
    int m = *std::max_element(Constants::squareIndices.begin(), Constants::squareIndices.end());

    // Floor and block control
    for (int z = 0; z < 2; ++z) {
        // Chunk iteration
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                for (size_t i = 0; i < Constants::square.size(); i += 3) {
                    initVertices.push_back(Constants::square.at(i) + (GLfloat) x);
                    initVertices.push_back(Constants::square.at(i + 1) + (GLfloat) y);
                    initVertices.push_back(Constants::square.at(i + 2) + (z == 0 ? 0 : 0.0001f));
                }

                size_t offset = indices.size() / Constants::squareIndices.size() * (m + 1);
                for (size_t i = 0; i < Constants::squareIndices.size(); ++i) {
                    indices.push_back(static_cast<GLint>(Constants::squareIndices.at(i) + offset));
                }
            }
        }
    }

    model->createOrSubdataVBO(0, 3, initVertices);
    model->createVBO(1, 2, totalUVCoords);
    model->bindIndexBuffer(indices);

    glBindVertexArray(0);
}

void MapLayers::regenerateLayerGraphics() {
    glBindVertexArray(model->vaoID);
    
    auto& layer = layers.at(this->layer);
    auto& textures = Context::getInstance().texturePack;
    auto& air = textures->getTextureMetadata("genesis:air").uvCoordinates;

    std::vector<GLfloat> uvs;
    // These variables serve no other purpose than ensuring the number doesn't become some magic number I don't
    // understand the next time I look at this
    auto dims = width * height;
    // with this as an excption. For tile.block, dimsWithlayers acts as the offset.
    auto dimsWithLayers = dims * 2;
    const auto numFloats = 4 * 2;
    auto uvFloatCount = dimsWithLayers * numFloats;
    auto blockOffset = dims * numFloats;

    uvs.resize(uvFloatCount);
    // This is suboptimal
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            auto tile = layer.layer.at(x).at(y);
            
            auto blockUVs = air;
            auto floorUVs = air;

            if (tile.block) {
                blockUVs = textures->getTextureMetadata(tile.block->tileID).uvCoordinates;
            }
            if (tile.floor) {
                floorUVs = textures->getTextureMetadata(tile.floor->tileID).uvCoordinates;
            }

            for (size_t i = 0; i < blockUVs.size(); ++i) {
                // The size is guaranteed to be identical between the two UV types

                // represents the offset to get match the vertices for a given tile
                auto tileOffset = x * height * blockUVs.size() + y * blockUVs.size() + i;
                uvs[tileOffset] = floorUVs[i]; 
                // + blockOffset offsets the tileOffset to ensure it's relative to the block UVs instead.
                uvs[tileOffset + blockOffset] = blockUVs[i]; 
            }

        }
    }

    model->createOrSubdataVBO(1, 2, uvs);
    glBindVertexArray(0);
}

}
