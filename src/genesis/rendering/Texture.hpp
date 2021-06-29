#pragma once

#include "GL/glew.h"
#include <string>
#include <vector>

namespace genesis {

class Texture {
protected:
    GLuint textureId;
    int width, height;
    int atlasWidth, atlasHeight;
    // TODO: figure out what this is actually for
    // (generated by stb, not sure what it does)
    int comp;

public:
    Texture() = default;
    Texture(const std::string& image, int atlasWidth = -1, int atlasHeight = -1);
    virtual ~Texture();

    void bind();
    void unbind();

    int getWidth() {
        return width;
    }
    int getHeight() {
        return height;
    }

    int getAtlasTileWidth() {
        return atlasWidth;
    }
    int getAtlasTileHeight() {
        return atlasHeight;
    }

    GLuint getID() {
        return textureId;
    }

    // Texture atlas helper
    // Generates UV coordinates from the given image x and image y.
    // If a width and height is supplied
    virtual std::vector<GLfloat> generateFromPosition(unsigned int x = 0, unsigned int y = 0, int width = -1, int height = -1);
};

} // namespace genesis
