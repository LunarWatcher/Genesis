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
    GLenum mode = GL_STATIC_DRAW;

    int vertices;
    size_t attribArrays = 0;
    GLuint vaoID;
    std::vector<GLuint> vbos;

    bool hasIndexBuffer = false;

    void createVAO();

    Model() = default;

public:
    Model(VertexArray vertices, AttributeInit attribInitFunc, int vertSize = 3, GLenum mode = GL_STATIC_DRAW);

    virtual ~Model();

    virtual void render() override;

    virtual void bindIndexBuffer(const IndexArray& indexBuffer);
    /**
     * Creates a VBO using the class-level mode
     */
    virtual void createVBO(unsigned int attribNumber, int coordSize, const VertexArray& data);

    /**
     * Creates a VBO using a different mode than that defined in the class.
     */
    virtual void createVBO(unsigned int attribNumber, int coordSize, const VertexArray& data, GLenum mode);

    /**
     * Allocates a VBO of size {@size}, but without initializing any data.
     * This MUST be done with glBufferSubData() at a later time.
     * Consequentially, the mode used is GL_DYNAMIC_DRAW
     */
    virtual void createVBO(unsigned int attribNumber, int coordSize, GLsizeiptr size);
};

} // namespace genesis
