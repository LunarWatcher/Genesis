#include "ParticleEmitter.hpp"
#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Renderer.hpp"

#include <iostream>

namespace genesis {

ParticleEmitter::ParticleEmitter() {

    createVAO();

    auto constexpr size = 100;
    // Position + age
    createVBO(0, 3, size * 3);
    // Scale
    createVBO(1, 4, size * 4);
    createVBO(2, 1, size);

    glm::vec4 color(1.0, 0.0, 1.0, 1.0);

    for (int i = 0; i < size; ++i) {
        // clang-format off
        Particle p{glm::vec3{ 1.0, 1.0, -2.0 },
            { cos(0.1 + ((double) i) * 7 / 100.0), sin(0.1 + ((double) i) * 7 / 100.0), 0.0 },
            10.0};
        // clang-format on
        this->particles.push_back(p);

        glNamedBufferSubData(this->vbos[0], i * 3 * sizeof(float), 3 * sizeof(float), &p.position[0]);
        glNamedBufferSubData(this->vbos[1], i * 4 * sizeof(float), 4 * sizeof(float), &color[0]);
        glNamedBufferSubData(this->vbos[2], i * sizeof(float), sizeof(float), &p.scale);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ParticleEmitter::render() {
    // TODO: move to an update method {{{
    for (size_t i = 0; i < this->particles.size(); ++i) {
        auto& particle = this->particles.at(i);
        particle.position += glm::vec3(particle.velocity) * (float) Renderer::getInstance().getDelta();

        glNamedBufferSubData(this->vbos[0], i * 3 * sizeof(float), 3 * sizeof(float), &particle.position[0]);
    }
    // }}}
    glBindVertexArray(this->vaoID);
    for (size_t i = 0; i < attribArrays; ++i) {
        glEnableVertexAttribArray(i);
    }
    // glVertexAttribDivisor(0, 0);
    // glVertexAttribDivisor(1, 1);
    // glVertexAttribDivisor(2, 6);

    //// We draw the vertices as an instanced thing
    // glDrawElementsInstanced(GL_TRIANGLES, indices, GL_UNSIGNED_INT, nullptr, particles.size());
    // glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glDrawArrays(GL_POINTS, 0, this->particles.size());

    for (size_t i = 0; i < attribArrays; ++i) {
        glDisableVertexAttribArray(i);
    }
    glBindVertexArray(0);
}

} // namespace genesis
