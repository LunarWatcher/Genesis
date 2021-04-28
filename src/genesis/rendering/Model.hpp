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
    int vertices;
    size_t attribArrays = 0;
    GLuint vaoID;
    std::vector<GLuint> vbos;

    void createVAO();

public:
    Model(VertexArray vertices, AttributeInit attribInitFunc);

    virtual ~Model();

    virtual void render(DefaultShader&) override;

    void bindIndexBuffer(const IndexArray& indexBuffer);
    void createVBO(int attribNumber, int size, const VertexArray& data);
};

class TexturedModel : public Renderable {
private:
    std::shared_ptr<Model> model;
    std::shared_ptr<Texture> texture;

public:
    TexturedModel(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture) : model(model), texture(texture) {}

    void render(DefaultShader&) override;
};

} // namespace genesis
