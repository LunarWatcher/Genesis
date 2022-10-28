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
#include "genesis/rendering/debug/DebugScene.hpp"

namespace genesis {

Chunk::Chunk(int chunkX, int chunkY) : Entity(std::make_shared<Model>(), glm::vec3{chunkX * Constants::Chunks::CHUNK_SIZE, chunkY * Constants::Chunks::CHUNK_SIZE, 0}), chunkX(chunkX), chunkY(chunkY) {
    Renderer::getInstance().getSceneByType<World>()->getNoiseGenerator()->generateChunk(this->chunkMap, chunkX, chunkY);
    model->mode = GL_DYNAMIC_DRAW;
    model->createVAO();
    // when we create the VBO, we want to allocate the entire thing in VRAM.
    // A lot of this will be unused, but whatever. I have no idea what I'm doing, this is good enough.
    model->createVBO(0, 3, 3ll * Constants::Chunks::WORST_CASE_SIZE);
    model->createVBO(1, 2, 2ll * Constants::Chunks::WORST_CASE_SIZE);
    model->bindIndexBuffer(2ll * Constants::Chunks::WORST_CASE_SIZE);
    for (int x = 0; x < Constants::Chunks::CHUNK_SIZE; ++x) {
        for (int y = 0; y < Constants::Chunks::CHUNK_SIZE; ++y) {
            this->chunkMap.at(Constants::Chunks::CHUNK_SEA_LEVEL).at(y).at(x) = DataHelper::getInstance()->getTileGenerator("genesis:grass")
                ->generateTile();
        }
    }
    regenerateVertices();
    glBindVertexArray(0);

    initializeCollider(std::make_shared<Rectangle>(0, 0, 0, Constants::Chunks::CHUNK_SIZE, Constants::Chunks::CHUNK_SIZE));
    collider->update(*this);
}

void Chunk::regenerateVertices() {

    glBindVertexArray(model->vaoID);
    std::vector<GLfloat> uv;
    std::vector<GLfloat> points;
    std::vector<int> indices;

    // What the fuck
    int m = *std::max_element(Constants::squareIndices.begin(), Constants::squareIndices.end());

    int baseLevel = Renderer::getInstance().getCamera()->getActiveY();
    auto& baseTiles = chunkMap.at(baseLevel);
    auto& floorTiles = chunkMap.at(baseLevel - 1);

    for (int x = 0; x < Constants::Chunks::CHUNK_SIZE; ++x) {
        for (int y = 0; y < Constants::Chunks::CHUNK_SIZE; ++y) {
            // This nasty shit opens some FOV weirdness
            bool baseIsEmpty = baseTiles.at(y).at(x) == nullptr;
            if (baseIsEmpty && floorTiles.at(y).at(x) == nullptr) continue;
            auto tile = baseIsEmpty ? floorTiles.at(y).at(x) : baseTiles.at(y).at(x);

            auto& uvSource = Renderer::getInstance().getTexturePack()->getTextureMetadata(tile->tileID).uvCoordinates;

            std::vector<GLfloat> blockVertices;
            for (size_t i = 0; i < Constants::square.size(); i += 3) {
                blockVertices.push_back(Constants::square.at(i) + (GLfloat) x);
                blockVertices.push_back(Constants::square.at(i + 1) + (GLfloat) y);
                blockVertices.push_back(Constants::square.at(i + 2) + (baseIsEmpty ? 0.0f : 1.0f));
            }

            size_t offset = indices.size() / Constants::squareIndices.size() * (m + 1);

            for (size_t i = 0; i < Constants::squareIndices.size(); ++i) {
                indices.push_back(static_cast<GLint>(Constants::squareIndices.at(i) + offset));
            }
            points.insert(points.end(), blockVertices.begin(), blockVertices.end());
            uv.insert(uv.end(), uvSource.begin(), uvSource.end());
        }
    }

    model->vertices = static_cast<GLint>(points.size());
    model->createOrSubdataVBO(0, 3, points);
    model->createOrSubdataVBO(1, 2, uv);
    model->bindIndexBuffer(indices);
}

void Chunk::render() {
    // we actually don't need to do much here for now; all the rendering is handled via the pre-cached mesh
    Entity::render();
}

} // namespace genesis
