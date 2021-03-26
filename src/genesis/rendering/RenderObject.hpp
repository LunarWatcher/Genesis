#pragma once

#include "GL/glew.h"
#include <vector>
#include <memory>

namespace genesis {

typedef std::vector<GLfloat> VertexArray;



class RenderObject {
protected:

    int vertices;
    GLuint vaoID;
    std::vector<GLuint> vbos;

    void createVAO();
    void createVBO(int attribNumber, int size, const VertexArray& data);
public:
    RenderObject(const VertexArray& vertices);
    virtual ~RenderObject();

    virtual void render();
};

}
