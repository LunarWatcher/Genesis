#pragma once

#include "GL/glew.h"
#include "genesis/rendering/Model.hpp"
#include "genesis/rendering/Texture.hpp"

#include <memory>

namespace genesis {

class Framebuffer {
private:
    GLuint fbo, rbo;
    std::unique_ptr<Texture> tex;
    std::unique_ptr<Model> model;

public:
    Framebuffer(int width, int height);
    Framebuffer(int x, int y, int width, int height);

    ~Framebuffer();

    void bind();
    void unbind();

    void render();

};

}
