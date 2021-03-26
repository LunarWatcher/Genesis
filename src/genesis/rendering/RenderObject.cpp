#include "RenderObject.hpp"
#include <stdexcept>
#include <vector>

namespace genesis {

RenderObject::RenderObject(const std::vector<GLfloat>& vertices) {
    this->vertices = vertices.size();
    generateVao();
    registerAttribute(vertices, 3, 0);

}

RenderObject::RenderObject(const VertexArray& vertices, const VertexArray& uvCoords, std::shared_ptr<Texture> texture) {
    this->vertices = vertices.size();
    generateVao();
    registerAttribute(vertices, 3, 0);
    registerAttribute(uvCoords, 2, 1);
}

GLuint RenderObject::generateBuffer(const std::vector<GLfloat>& vertices) {
    GLuint vertexArrayId;
    GLuint buffIdx;
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    glGenBuffers(1, &buffIdx);
    glBindBuffer(GL_ARRAY_BUFFER, buffIdx);
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size(),
                 &vertices[0], GL_STATIC_DRAW);
    return buffIdx;
}

void RenderObject::generateVao() {
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
}

void RenderObject::render() {
    if (attribs.size() == 0) {
        throw std::runtime_error("Can't have 0 attributes");
    }
    for (auto& attribute : attribs) {
        attribute->enable();
    }
    glDrawArrays(GL_TRIANGLES, 0, this->vertices);
    for (long long i = attribs.size() - 1; i >= 0; --i) {
        attribs.at(i)->disable();
    }
}

void RenderObject::registerAttribute(const std::vector<GLfloat>& attribute, GLint dataSize, GLint shaderAttribIdx) {
    this->attribs.push_back(std::make_shared<FloatAttribArray>(generateBuffer(attribute), dataSize, shaderAttribIdx));
}

}
