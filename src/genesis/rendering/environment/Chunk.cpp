#include "Chunk.hpp"
#include "genesis/core/WorldController.hpp"
#include "genesis/math/Perlin.hpp"
#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/atlases/TextureAtlas.hpp"
#include "genesis/rendering/shaders/DefaultShader.hpp"
#include <algorithm>

namespace genesis {

Chunk::Chunk(int chunkX, int chunkY) : Entity(std::make_shared<Model>(), glm::vec3{chunkX * 16, chunkY * 16, 0}), chunkX(chunkX), chunkY(chunkY) {
    Renderer::getInstance().getSceneByType<WorldController>()->getNoiseGenerator()->generateChunk(this->chunkMap, chunkX, chunkY);
    model->mode = GL_DYNAMIC_DRAW;
    model->createVAO();
    // when we create the VBO, we want to
    model->createVBO(0, 3, 3 * Constants::Chunks::WORST_CASE_SIZE);
    model->createVBO(1, 2, 2 * Constants::Chunks::WORST_CASE_SIZE);
    model->bindIndexBuffer(2 * Constants::Chunks::WORST_CASE_SIZE);
    for (int x = 0; x < Constants::Chunks::CHUNK_SIZE; ++x) {
        for (int y = 0; y < Constants::Chunks::CHUNK_SIZE; ++y) {
            this->chunkMap.at(0).at(y).at(x) = "genesis:dirt";
        }
    }
    regenerateVertices();
    glBindVertexArray(0);
}

void Chunk::regenerateVertices() {

    auto& uvSource = Renderer::getInstance().getTexturePack()->getTextureMetadata("genesis:grass").uvCoordinates;

    auto uv = uvSource;
    std::vector<GLfloat> points;
    std::vector<int> indices;

    int m = *std::max_element(Constants::squareIndices.begin(), Constants::squareIndices.end());

    for (int x = 0; x < Constants::Chunks::CHUNK_SIZE; ++x) {
        for (int y = 0; y < Constants::Chunks::CHUNK_SIZE; ++y) {
            std::vector<GLfloat> blockVertices;

            for (size_t i = 0; i < Constants::square.size(); i += 3) {
                blockVertices.push_back(Constants::square.at(i) + (GLfloat) x);
                blockVertices.push_back(Constants::square.at(i + 1) + (GLfloat) y);
                blockVertices.push_back(Constants::square.at(i + 2));
            }

            size_t offset = indices.size() / Constants::squareIndices.size() * (m + 1);

            for (size_t i = 0; i < Constants::squareIndices.size(); ++i) {
                indices.push_back(Constants::squareIndices.at(i) + offset);
            }
            points.insert(points.end(), blockVertices.begin(), blockVertices.end());
            uv.insert(uv.end(), uvSource.begin(), uvSource.end());
        }
    }

    model->createVBO(1, 2, uv);
    model->vertices = points.size();
    model->createVBO(0, 3, points, GL_DYNAMIC_DRAW);
    model->bindIndexBuffer(indices);
}

void Chunk::render() {
    if (!chunkMap.contains(Renderer::getInstance().getCamera()->getActiveY()))
        return;
    auto& currLevel = chunkMap.at(Renderer::getInstance().getCamera()->getActiveY());
    Entity::render();
}

} // namespace genesis
