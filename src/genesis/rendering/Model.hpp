#pragma once

#include "GL/glew.h"
#include "Renderable.hpp"
#include "genesis/rendering/Texture.hpp"
#include <functional>
#include <memory>
#include <stdexcept>
#include <vector>

namespace genesis {

typedef std::vector<GLfloat> VertexArray;
typedef std::vector<GLint> IndexArray;
class Model;
typedef std::function<void(Model*)> AttributeInit;

class Model : public Renderable {
protected:
    GLenum mode;

    int vertices;
    size_t attribArrays = 0;
    GLuint vaoID;
    std::vector<GLuint> vbos;

    void createVAO();

public:
    Model(VertexArray vertices, AttributeInit attribInitFunc, GLenum mode = GL_STATIC_DRAW);

    virtual ~Model();

    virtual void render() override;

    void bindIndexBuffer(const IndexArray& indexBuffer);
    void createVBO(int attribNumber, int size, const VertexArray& data);
};

} // namespace genesis
