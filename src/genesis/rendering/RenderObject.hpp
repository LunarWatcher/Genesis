#pragma once

#include "GL/glew.h"
#include <vector>
#include <memory>

namespace genesis {

typedef std::vector<GLfloat> VertexArray;

class Texture;

class AttribArray {
public:
    virtual ~AttribArray() = default;
    virtual void enable() = 0;
    virtual void disable() = 0;
};

class FloatAttribArray : public AttribArray {
protected:
    GLuint bufferIdx;
    GLint dataSize;
    GLint shaderAttribIdx;

    FloatAttribArray() = default;
public:
    FloatAttribArray(GLuint bufferIdx, GLint dataSize, GLint shaderAttribIdx)
        : bufferIdx(bufferIdx), dataSize(dataSize), shaderAttribIdx(shaderAttribIdx) {}
    virtual ~FloatAttribArray() = default;

    virtual void enable() override {
        glEnableVertexAttribArray(shaderAttribIdx);
        glBindBuffer(GL_ARRAY_BUFFER, bufferIdx);
        glVertexAttribPointer(shaderAttribIdx, dataSize, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    }

    virtual void disable() override {
        glDisableVertexAttribArray(shaderAttribIdx);
    }

    friend class RenderObject;    
};

class RenderObject {
protected:
    std::vector<std::shared_ptr<AttribArray>> attribs;

    int vertices;
    GLuint vaoID;

    GLuint generateBuffer(const VertexArray& vertices);

public:
    RenderObject(const VertexArray& vertices);
    RenderObject(const VertexArray& vertices, const VertexArray& uvCoords, std::shared_ptr<Texture> texture);
    void registerAttribute(const std::vector<GLfloat>& attribute, GLint dataSize, GLint shaderAttribIdx);
    void generateVao();

    virtual ~RenderObject() = default;

    virtual void render();
};

}
