#include "Model.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
namespace genesis {

Model::Model(VertexArray vertices, std::function<void(Model*)> attribInitFunc, GLenum mode) : mode(mode) {
    this->vertices = vertices.size();
    createVAO();
    createVBO(0, 3, vertices);
    attribInitFunc(this);
    glBindVertexArray(0);
}

Model::~Model() {
    glDeleteVertexArrays(1, &vaoID);
    glDeleteBuffers(this->vbos.size(), &vbos[0]);
}

void Model::bindIndexBuffer(const IndexArray& indexBuffer) {
    GLuint vboId;
    glGenBuffers(1, &vboId);
    this->vbos.push_back(vboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.size() * sizeof(GLint), &indexBuffer[0], mode);
}

void Model::createVAO() {
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
}

void Model::createVBO(int attribNumber, int coordSize, const VertexArray& data) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    attribArrays += 1;
    this->vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], mode);
    glVertexAttribPointer(attribNumber, coordSize, GL_FLOAT, false, 0, (void*) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::render() {
    glBindVertexArray(this->vaoID);
    for (size_t i = 0; i < attribArrays; ++i) {
        glEnableVertexAttribArray(i);
    }
    glDrawElements(GL_TRIANGLES, vertices, GL_UNSIGNED_INT, 0);
    for (size_t i = 0; i < attribArrays; ++i) {
        glDisableVertexAttribArray(i);
    }
    glBindVertexArray(0);
}

} // namespace genesis
