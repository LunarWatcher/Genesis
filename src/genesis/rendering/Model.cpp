#include "Model.hpp"
#include <stdexcept>
#include <vector>
#include <iostream> 
namespace genesis {

Model::Model(const VertexArray& vertices, const IndexArray& indexBuffer) {
    this->vertices = vertices.size();
    createVAO();
    bindIndexBuffer(indexBuffer);
    createVBO(0, 3, vertices);
    glBindVertexArray(0);
}

Model::Model(const VertexArray& vertices, const IndexArray& indexBuffer, const VertexArray& uvCoords) {
    this->vertices = vertices.size();
    // TODO: refactor to avoid copy-pasta between the two (and any future) constructors
    createVAO();
    bindIndexBuffer(indexBuffer);
    createVBO(0, 3, vertices);
    createVBO(1, 2, uvCoords);
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.size() * sizeof(GLint), &indexBuffer[0], GL_STATIC_DRAW);

}

void Model::createVAO() {
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
}

void Model::createVBO(int attribNumber, int coordSize, const VertexArray& data) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    this->vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(attribNumber, coordSize, GL_FLOAT, false, 0, (void*) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::render() {
    glBindVertexArray(this->vaoID);
    for (size_t i = 0; i < vbos.size(); ++i) {
        glEnableVertexAttribArray(i);
    }
    glDrawElements(GL_TRIANGLES, vertices, GL_UNSIGNED_INT, 0);
    for (size_t i = 0; i < vbos.size(); ++i) {
        glDisableVertexAttribArray(i);
    }
    glBindVertexArray(0);
}

void TexturedModel::render() {
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, this->texture->getID());
    this->model->render();
}

}
