#pragma once

#include "GL/glew.h"
#include "genesis/rendering/Texture.hpp"
#include "Renderable.hpp"
#include <stdexcept>
#include <vector>
#include <memory>

namespace genesis {

typedef std::vector<GLfloat> VertexArray;
typedef std::vector<GLint> IndexArray;

class Model : public Renderable {
protected:

    int vertices;
    size_t attribArrays = 0;
    GLuint vaoID;
    std::vector<GLuint> vbos;

    void createVAO();
    void createVBO(int attribNumber, int size, const VertexArray& data);
    void bindIndexBuffer(const IndexArray& indexBuffer);
public:
    Model(const VertexArray& vertices, const IndexArray& indexBuffer);
    Model(const VertexArray& vertices, const IndexArray& indexBuffer, const VertexArray& uvCoords);
    virtual ~Model();

    virtual void render(DefaultShader&) override;
};


class TexturedModel : public Renderable {
private:
    std::shared_ptr<Model> model;
    std::shared_ptr<Texture> texture;
public:
    TexturedModel(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture)
        : model(model), texture(texture) {}

    void render(DefaultShader&) override;
};

}
