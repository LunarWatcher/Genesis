#pragma once

#include "GL/glew.h"

#include "Renderable.hpp"
#include "genesis/rendering/Texture.hpp"

#include <functional>
#include <memory>
#include <stdexcept>
#include <vector>

namespace genesis {

class Entity;
class Collider;

typedef std::vector<GLfloat> VertexArray;
typedef std::vector<GLint> IndexArray;

typedef std::function<void (Entity*)> AttributeInit;

class Entity : public Renderable {
private:
    void init(const VertexArray& vertices, const AttributeInit& attribInitFunc, int coordSize);
protected:
    // Model meta {{{
    GLenum renderMode = GL_STATIC_DRAW;
    GLenum renderType = GL_TRIANGLES;

    size_t vertices, indices = -1;
    GLuint vaoID;
    std::vector<GLuint> vbos;

    bool hasIndexBuffer = false;
    // }}}
    // Entity meta {{{
    glm::vec3 position, rotation;
    // Keeping the scale a float instead of a vector,
    // because I don't see any practical use of a vector scale.
    float scale;

    glm::mat4 transMatrix;
    // }}}

    void createVAO();


    /**
     * ONLY supported for internal use in overriding classes that need a separate
     * initialisation flow.
     */
    Entity() = default;
public:
    /**
     * "Raw" model initialisation.
     * Doesn't handle the entity attributes.
     */
    Entity(const VertexArray& vertices, const AttributeInit& attribInitFunc, int vertSize = 3);

    /**
     *
     */
    Entity(const VertexArray& vertices, const AttributeInit& attribInitFunc,
            const glm::vec3& position, const glm::vec3& rotation, const int& vertSize = 3, const float& scale = 1);

    virtual ~Entity();

    virtual void tick();
    virtual void render() override;

    // OpenGL buffers {{{
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
    // }}}

    /**
     * Glorified `with` (python) alternative.
     * Calls regenerateTransMatrix() when the block is done iff the callback
     * returns true
     */
    void modify(const std::function<bool()>& callback) {
        if (callback()) {
            regenerateTransMatrix();
        }
    }

    void regenerateTransMatrix();

    void setRenderType(GLenum renderType) {
        this->renderType = renderType;
    }

    void setRenderMode(GLenum renderMode) {
        this->renderMode = renderMode;
    }
};

} // namespace genesis
