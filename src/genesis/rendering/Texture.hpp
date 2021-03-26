#pragma once

#include "GL/glew.h"
#include <string>

namespace genesis {

class Texture {
private:
    GLuint textureId;
    int width, height;
    // TODO: figure out what this is actually for
    int comp;
public:
    Texture(const std::string& image);

    int getWidth() { return width; }
    int getHeight() { return height; }
};

}
