#include "Model.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

namespace genesis {

Model::Model(const VertexArray& vertices, const std::function<void(Model*)>& attribInitFunc, int coordSize, GLenum mode)
        : mode(mode) {
    createVAO();
    createOrSubdataVBO(0, coordSize, vertices); // NOLINT
    if (attribInitFunc) {
        attribInitFunc(this);
    }
    glBindVertexArray(0);

    this->vertices = vertices.size() / (this->hasIndexBuffer ? 1 : coordSize);
}

Model::~Model() {
    glDeleteVertexArrays(1, &vaoID);
    std::vector<GLuint> _vbos;
    for (auto& [_, vbo] : vbos) _vbos.push_back(vbo);
    glDeleteBuffers(static_cast<GLsizei>(_vbos.size()), _vbos.data());
}

void Model::bindIndexBuffer(const IndexArray& indexBuffer) {
    this->indices = indexBuffer.size();
    if (!hasIndexBuffer) {
        this->hasIndexBuffer = true;
        GLuint vboId = 0;
        glGenBuffers(1, &vboId);
        vbos[-1] = vboId;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[-1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indexBuffer.size() * sizeof(GLint)), indexBuffer.data(), mode);
    } else {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos.at(-1));
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(indexBuffer.size() * sizeof(GLint)), indexBuffer.data());
    }
}

void Model::bindIndexBuffer(GLsizeiptr size) {
    this->hasIndexBuffer = true;
    GLuint vboId = 0;
    glGenBuffers(1, &vboId);
    vbos[-1] = vboId;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(size * sizeof(GLint)), 0, GL_DYNAMIC_DRAW);
}

void Model::createVAO() {
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
}

void Model::createOrSubdataVBO(unsigned int attribNumber, int coordSize, const VertexArray& data) {
    if (!vbos.contains(attribNumber)) {
        createVBO(attribNumber, coordSize, data, this->mode); // NOLINT
    } else {
        if (mode != GL_DYNAMIC_DRAW) {
            throw std::runtime_error("Attempted to reuse attribute " + std::to_string(attribNumber) + " (current size: " + std::to_string(vbos.size()) + ")");
        }
        auto vbo = this->vbos.at(attribNumber);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(data.size() * sizeof(GLfloat)), data.data());
        glVertexAttribPointer(attribNumber, coordSize, GL_FLOAT, false, 0, (void*) 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void Model::createOrResizeVBO(unsigned int attribNumber, int coordSize, const VertexArray &data) {
    if (!vbos.contains(attribNumber)) {
        createVBO(attribNumber, coordSize, data, this->mode); // NOLINT
    } else {
        if (mode != GL_DYNAMIC_DRAW) {
            throw std::runtime_error("Attempted to reuse attribute " + std::to_string(attribNumber) + " (current size: " + std::to_string(vbos.size()) + ")");
        }
        auto vbo = this->vbos.at(attribNumber);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(data.size() * sizeof(GLfloat)), data.data(), GL_DYNAMIC_DRAW);
        glVertexAttribPointer(attribNumber, coordSize, GL_FLOAT, false, 0, (void*) 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void Model::createVBO(unsigned int attribNumber, int coordSize, const VertexArray& data, GLenum mode) {
    if (vbos.contains(attribNumber)) {
        throw std::runtime_error("VBO already registered");
    }
    GLuint vboID = 0;
    glGenBuffers(1, &vboID);
    vbos[attribNumber] = vboID;
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(data.size() * sizeof(GLfloat)), data.data(), mode);
    // these only need to be enabled once
    glEnableVertexAttribArray(attribNumber);
    glVertexAttribPointer(attribNumber, coordSize, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::createVBO(unsigned int attribNumber, int coordSize, GLsizeiptr size) {
    GLuint vboID = 0;
    glGenBuffers(1, &vboID);
    vbos[attribNumber] = vboID;
    glBindBuffer(GL_ARRAY_BUFFER, vboID); // NOLINT

    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size * sizeof(GLfloat)), nullptr, GL_DYNAMIC_DRAW);
    // These only need to be enabled once
    glEnableVertexAttribArray(attribNumber);
    glVertexAttribPointer(attribNumber, coordSize, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::render() {
    glBindVertexArray(this->vaoID);
    if (hasIndexBuffer) {
        glDrawElements(renderType, indices, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(renderType, 0, vertices);
    }
    glBindVertexArray(0);
}

} // namespace genesis
