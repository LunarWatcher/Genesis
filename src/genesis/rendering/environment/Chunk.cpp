#include "Chunk.hpp"
#include "genesis/core/WorldController.hpp"
#include "genesis/math/Perlin.hpp"
#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/atlases/TextureAtlas.hpp"
#include "genesis/rendering/shaders/DefaultShader.hpp"

namespace genesis {

Chunk::Chunk(int chunkX, int chunkY) : Entity(std::make_shared<Model>(), glm::vec3{chunkX * 16, chunkY * 16, 0}), chunkX(chunkX), chunkY(chunkY) {
    Renderer::getInstance().getSceneByType<WorldController>()->getNoiseGenerator()->generateChunk(this->chunkMap, chunkX, chunkY);
    model->mode = GL_DYNAMIC_DRAW;
    model->createVAO();

    regenerateVertices();
    glBindVertexArray(0);
}

void Chunk::regenerateVertices() {
    std::vector<GLfloat> points = Constants::cube;

    model->createVBO(0, 3, points);
    auto uvSource = Renderer::getInstance().getTexturePack()->generateFromPosition(
        Renderer::getInstance().getTexturePack()->decodeCoordinates((int) WorldTile::GRASS)
    );
    auto uv = uvSource;
    for (int i = 0; i < 6; ++i)
        uv.insert(uv.end(), uvSource.begin(), uvSource.end());
    model->createVBO(1, 2, uv);
    model->bindIndexBuffer(Constants::fullCubeIndices);
    model->vertices = points.size();
}

void Chunk::render() {
    if (!chunkMap.contains(Renderer::getInstance().getCamera()->getActiveY()))
        return;
    auto& currLevel = chunkMap.at(Renderer::getInstance().getCamera()->getActiveY());

    Entity::render();
}

} // namespace genesis
