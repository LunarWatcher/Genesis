#include "ParticleEmitter.hpp"
#include "genesis/rendering/Constants.hpp"

namespace genesis {

ParticleEmitter::ParticleEmitter() {
    auto& vertices = Constants::square;
    this->vertices = vertices.size();

    createVAO();

    // Bind the index buffer
    bindIndexBuffer(Constants::squareIndices);
    // Bind the vertices
    createVBO(0, 3, vertices);
    // The rest is dynamic

    // Position + age
    createVBO(1, 3, 100 * 4 * sizeof(GLfloat));
    // Scale
    createVBO(2, 1, 100 * sizeof(GLfloat));

    for (int i = 0; i < 100; ++i) {
        Particle p{glm::vec4{1.0 + i, 1.0 + i, -2.0, 1.0}, 1.0};
        this->particles.push_back(p);

        glBindBuffer(GL_ARRAY_BUFFER, this->vbos[1]);
        glBufferSubData(GL_ARRAY_BUFFER, i * 4, 4 * sizeof(float), &p.position[0]);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbos[2]);
        glBufferSubData(GL_ARRAY_BUFFER, i, sizeof(float), &p.scale);
    }

    glBindVertexArray(0);
}

void ParticleEmitter::render() {
    glBindVertexArray(this->vaoID);
    for (size_t i = 0; i < attribArrays; ++i) {
        glEnableVertexAttribArray(i);
    }
    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);

    // We draw the vertices as an instanced thing
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, particles.size());

    for (size_t i = 0; i < attribArrays; ++i) {
        glDisableVertexAttribArray(i);
    }
    glBindVertexArray(0);
}

} // namespace genesis
