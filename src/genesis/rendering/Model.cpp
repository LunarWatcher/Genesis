#include "Model.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

namespace genesis {

Model::Model(VertexArray vertices, std::function<void(Model*)> attribInitFunc, int coordSize, GLenum mode)
        : mode(mode) {
    createVAO();
    createVBO(0, coordSize, vertices);
    attribInitFunc(this);
    glBindVertexArray(0);

    this->vertices = vertices.size() / (this->hasIndexBuffer ? 1 : coordSize);
}

Model::~Model() {
    glDeleteVertexArrays(1, &vaoID);
    glDeleteBuffers(this->vbos.size(), vbos.data());
}

void Model::bindIndexBuffer(const IndexArray& indexBuffer) {
    this->indices = indexBuffer.size();
    this->hasIndexBuffer = true;
    GLuint vboId;
    glGenBuffers(1, &vboId);
    this->vbos.push_back(vboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.size() * sizeof(GLint), indexBuffer.data(), mode);
}

void Model::createVAO() {
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
}

void Model::createVBO(unsigned int attribNumber, int coordSize, const VertexArray& data) {
    createVBO(attribNumber, coordSize, data, this->mode);
}

void Model::createVBO(unsigned int attribNumber, int coordSize, const VertexArray& data, GLenum mode) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    this->vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), mode);
    // these only need to be enabled once
    glEnableVertexAttribArray(attribNumber);
    glVertexAttribPointer(attribNumber, coordSize, GL_FLOAT, false, 0, (void*) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::createVBO(unsigned int attribNumber, int coordSize, GLsizeiptr size) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    this->vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);
    // These only need to be enabled once
    glEnableVertexAttribArray(attribNumber);
    glVertexAttribPointer(attribNumber, coordSize, GL_FLOAT, false, 0, (void*) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::render() {
    glBindVertexArray(this->vaoID);
    if (hasIndexBuffer) {
        glDrawElements(renderType, vertices, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(renderType, 0, vertices);
    }
    glBindVertexArray(0);
}

} // namespace genesis
