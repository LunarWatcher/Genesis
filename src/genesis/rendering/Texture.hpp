#pragma once

#include "GL/glew.h"
#include "genesis/rendering/RenderObject.hpp"
#include <string>

namespace genesis {

class Texture : public AttribArray {
private:
    GLuint textureId;
    int width, height;
    // TODO: figure out what this is actually for
    int comp;
public:
    Texture(const std::string& image);

    void enable() override {

    }
    void disable() override {

    }

    int getWidth() { return width; }
    int getHeight() { return height; }
};

}
