#include "Chunk.hpp"
#include "genesis/core/data/DataHelper.hpp"
#include "genesis/core/game/World.hpp"
#include "genesis/math/Perlin.hpp"
#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/atlases/TextureAtlas.hpp"
#include "genesis/rendering/shaders/DefaultShader.hpp"
#include <algorithm>

#include "genesis/math/physics/Rectangle.hpp"

namespace genesis {

Chunk::Chunk(int chunkX, int chunkY) : Entity(std::make_shared<Model>(), glm::vec3{chunkX * Constants::Chunks::CHUNK_SIZE, chunkY * Constants::Chunks::CHUNK_SIZE, 0}), chunkX(chunkX), chunkY(chunkY) {
    Renderer::getInstance().getSceneByType<World>()->getNoiseGenerator()->generateChunk(this->chunkMap, chunkX, chunkY);
    model->mode = GL_DYNAMIC_DRAW;
    model->createVAO();
    // when we create the VBO, we want to allocate the entire thing in VRAM.
    // A lot of this will be unused, but whatever. I have no idea what I'm doing, this is good enough.
    // Future me here; no. I'm fucking stupid.
    //
    // Even with 3D, the plan is discrete 3D, so later-wise rendering. This means three layers are rendered at most, making the worst case every tile being rendered
    // due to some other transparency mechanics.
    //
    // Even then, I should probably do something about the rendering system wrt. transparency, seeing as OpenGL is ass at dealing with it.
    // OpenGL is so bad at transparency that if you weren't paying attention, you'd think Stack Overflow was involved.
    model->createVBO(0, 3, 3ll * Constants::Chunks::WORST_CASE_SIZE);
    model->createVBO(1, 2, 2ll * Constants::Chunks::WORST_CASE_SIZE);
    model->bindIndexBuffer(2ll * Constants::Chunks::WORST_CASE_SIZE);

    regenerateVertices();
    glBindVertexArray(0);

    initializeCollider(std::make_shared<Rectangle>(0, 0, 0, Constants::Chunks::CHUNK_SIZE, Constants::Chunks::CHUNK_SIZE));
    collider->update(position);
}

void Chunk::regenerateVertices() {

    glBindVertexArray(model->vaoID);
    std::vector<GLfloat> uv;
    std::vector<GLfloat> points;

    // Alpha fuckery; Stuff has to be sorted, which is hard to do in a mesh like this.
    // I imagine there's still consequences down the line for doing this, particularly with
    // 3D-ish graphics later down the line, but fuck you future me, not my problem. Deal with it
    // Alternatively, I could just do this in layers and disregard whether or not something needs to be rendered.
    // It's inefficient, sure, but if it's just bound to like three layers, that isn't too big a sacrifice. 
    //
    // There's definitely overhead to address here, however.
    std::vector<GLfloat> latePoints, lateUV;

    std::vector<int> indices;

    // What the fuck
    int m = *std::max_element(Constants::squareIndices.begin(), Constants::squareIndices.end());

    int baseLevel = Renderer::getInstance().getCamera()->getActiveY();
    auto& baseTiles = chunkMap.at(baseLevel);
    auto& floorTiles = chunkMap.at(baseLevel - 1);


    // I hate myself for being inconsistent with which axis is the depth axis
    for (int x = 0; x < Constants::Chunks::CHUNK_SIZE; ++x) {
        for (int y = 0; y < Constants::Chunks::CHUNK_SIZE; ++y) {
            // This nasty shit opens some FOV weirdness

            std::vector<std::pair<int, std::vector<GLfloat>>> uvs;

            auto baseTile = baseTiles.at(y).at(x);
            if (baseTile == nullptr && floorTiles.at(y).at(x) == nullptr) continue;

            // First sweep; floor.
            if (baseTile == nullptr || !baseTile->isTextureSolid) {
                auto floorTile = floorTiles.at(y).at(x);
                auto uvSource = Renderer::getInstance().getTexturePack()->getTextureMetadata(floorTile->tileID).uvCoordinates;
                uvs.push_back({0, uvSource});
            }
            // Check floor tiles first to exploit ordering for indexing
            if (baseTile != nullptr) {
                auto uvSource = Renderer::getInstance().getTexturePack()->getTextureMetadata(baseTile->tileID).uvCoordinates;
                uvs.push_back({1, uvSource});
            }

            for (auto& [yOffset, uvSource] : uvs) {
                auto& pointRef = yOffset == 1 ? latePoints : points;
                auto& uvRef = yOffset == 1 ? lateUV : uv;

                std::vector<GLfloat> blockVertices;
                for (size_t i = 0; i < Constants::square.size(); i += 3) {
                    blockVertices.push_back(Constants::square.at(i) + (GLfloat) x);
                    blockVertices.push_back(Constants::square.at(i + 1) + (GLfloat) y);
                    blockVertices.push_back(Constants::square.at(i + 2) + yOffset);
                }

                size_t offset = indices.size() / Constants::squareIndices.size() * (m + 1);

                for (size_t i = 0; i < Constants::squareIndices.size(); ++i) {
                    indices.push_back(static_cast<GLint>(Constants::squareIndices.at(i) + offset));
                }
                pointRef.insert(pointRef.end(), blockVertices.begin(), blockVertices.end());
                uvRef.insert(uvRef.end(), uvSource.begin(), uvSource.end());
            }
        }
    }

    uv.insert(uv.end(), lateUV.begin(), lateUV.end());
    points.insert(points.end(), latePoints.begin(), latePoints.end());

    model->vertices = static_cast<GLint>(points.size());
    model->createOrSubdataVBO(0, 3, points);
    model->createOrSubdataVBO(1, 2, uv);
    model->bindIndexBuffer(indices);
}

void Chunk::render() {
    // This is horribly inefficient

    regenerateVertices();
    // we actually don't need to do much here for now; all the rendering is handled via the pre-cached mesh
    Entity::render();
}

int Chunk::getTopY(int x, int z) {

    for (auto y = Constants::MAX_OVERWORLD_HEIGHT; y >= -Constants::MAX_UNDERGROUND_HEIGHT; --y) {
        if (chunkMap.contains(y) && chunkMap.at(y).at(x).at(z) != nullptr) {
            return y;
        }
    }
    // Should never happen
    return -1;
}

void Chunk::set(std::shared_ptr<Tile> tile, int x, int z, int y) {
    chunkMap.at(y).at(x).at(z) = tile;
}

} // namespace genesis
