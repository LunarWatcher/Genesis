#pragma once

#include "GL/glew.h"

#include "Renderable.hpp"
#include "genesis/rendering/Texture.hpp"
#include "genesis/math/physics/Collider.hpp"

#include <functional>
#include <memory>
#include <stdexcept>
#include <vector>
#include <map>

namespace genesis {

typedef std::vector<GLfloat> VertexArray;
typedef std::vector<GLint> IndexArray;

class Model;
typedef std::function<void (Model*)> AttributeInit;

class Model : public Renderable {
protected:
    GLenum mode = GL_STATIC_DRAW;
    GLenum renderType = GL_TRIANGLES;

    size_t vertices, indices = -1;
    GLuint vaoID;
    std::map<unsigned int, GLuint> vbos;

    bool hasIndexBuffer = false;

    void createVAO();
public:
    /**
     * While public, DO NOT USE to construct models in any other context
     * than proper classes needing to use this to induce their own
     * model creation systems.
     *
     * Unless you're a class depending on an instance of Model, DO NOT
     * use this constructor. You WILL shoot yourself in the foot.
     */
    Model() = default;
    Model(const VertexArray& vertices, const AttributeInit& attribInitFunc, int vertSize = 3, GLenum mode = GL_STATIC_DRAW);

    virtual ~Model();

    virtual void render() override;

    virtual void bindIndexBuffer(const IndexArray& indexBuffer);
    /**
     * Creates a VBO using the class-level mode
     */
    virtual void createVBO(unsigned int attribNumber, int coordSize, const VertexArray& data);

    /**
     * Creates a VBO using a different mode than that defined in the class.
     *
     * This method may throw an instance of std::runtime_exception if
     * trying to assign an attribNumber that already exists.
     * Consequently, all VBOs are required to be in descending order,
     * and registered in descending order.
     *
     * But I shouldn't do that in the first place so this shouldn't be a problem
     * Odds are that no one but me is gonna read this anyway.
     *
     * Hi Livi :p
     */
    virtual void createVBO(unsigned int attribNumber, int coordSize, const VertexArray& data, GLenum mode);

    /**
     * Allocates a VBO of size {@size}, but without initializing any data.
     * This MUST be done with glBufferSubData() at a later time.
     * Consequentially, the mode used is GL_DYNAMIC_DRAW
     */
    virtual void createVBO(unsigned int attribNumber, int coordSize, GLsizeiptr size);

    void setRenderType(GLenum renderType) {
        this->renderType = renderType;
    }

    friend class TextEntity;
};

} // namespace genesis
