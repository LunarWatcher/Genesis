#include "RenderObject.hpp"
#include <stdexcept>
#include <vector>

namespace genesis {

RenderObject::RenderObject(const VertexArray& vertices) {
    this->vertices = vertices.size();
    createVAO();
    createVBO(0, 3, vertices);
    glBindVertexArray(0);
}

RenderObject::~RenderObject() {
    glDeleteVertexArrays(1, &vaoID);
    glDeleteBuffers(this->vbos.size(), &vbos[0]);
}

void RenderObject::createVAO() {
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
}

void RenderObject::createVBO(int attribNumber, int size, const VertexArray& data) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    this->vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(attribNumber, size, GL_FLOAT, false, 0, (void*) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderObject::render() {
    glBindVertexArray(this->vaoID);
    for (size_t i = 0; i < vbos.size(); ++i) {
        glEnableVertexAttribArray(i);
    }
    glDrawArrays(GL_TRIANGLES, 0, this->vertices);
    for (long long i = vbos.size() - 1; i >= 0; --i) {
        glDisableVertexAttribArray(i);
    }
    glBindVertexArray(0);
}


}
