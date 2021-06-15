#include "ParticleEmitter.hpp"
#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Renderer.hpp"

#include <iostream>

namespace genesis {

ParticleEmitter::ParticleEmitter() {
    this->vertices = Constants::square.size();

    createVAO();

    // Bind the index buffer
    bindIndexBuffer(Constants::squareIndices);
    // Bind the vertices
    createVBO(0, 3, Constants::square);
    // The rest is dynamic

    // Position + age
    createVBO(1, 4, 100 * 4);
    // Scale
    createVBO(2, 1, 100);

    for (int i = 0; i < 100; ++i) {
        // clang-format off
        Particle p{glm::vec4{ 1.0, 1.0, -2.0, 1.0 },
            { cos(0.1 + ((double) i) * 7 / 100.0), sin(0.1 + ((double) i) * 7 / 100.0), 0.0 },
            0.2};
        // clang-format on
        this->particles.push_back(p);

        glNamedBufferSubData(this->vbos[2], i * 4 * sizeof(float), 4 * sizeof(float), &p.position[0]);
        glNamedBufferSubData(this->vbos[3], i * sizeof(float), sizeof(float), &p.scale);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ParticleEmitter::render() {
    // TODO: move to an update method {{{
    for (size_t i = 0; i < this->particles.size(); ++i) {
        auto& particle = this->particles.at(i);
        particle.position += glm::vec4(particle.velocity, 0.0) * (float) Renderer::getInstance().getDelta();

        glNamedBufferSubData(this->vbos[2], i * 4 * sizeof(float), 4 * sizeof(float), &particle.position[0]);
    }
    // }}}
    glBindVertexArray(this->vaoID);
    for (size_t i = 0; i < attribArrays; ++i) {
        glEnableVertexAttribArray(i);
    }
    glVertexAttribDivisor(0, 0);
    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 6);

    // We draw the vertices as an instanced thing
    glDrawElementsInstanced(GL_TRIANGLES, indices, GL_UNSIGNED_INT, nullptr, particles.size());

    for (size_t i = 0; i < attribArrays; ++i) {
        glDisableVertexAttribArray(i);
    }
    glBindVertexArray(0);
}

} // namespace genesis
