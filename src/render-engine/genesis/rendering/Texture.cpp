#include "Texture.hpp"
#include <iostream>

#include "stb_image.h"

namespace genesis {

Texture::Texture(int width, int height) : width(width), height(height) {
    genTexture();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const std::string& file, int atlasWidth, int atlasHeight) {
    unsigned char* source = stbi_load(file.c_str(), &width, &height, &comp, STBI_rgb_alpha);

    genTexture();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, source);

    stbi_image_free(source);

    glBindTexture(GL_TEXTURE_2D, 0);

    this->atlasTileWidth = atlasWidth == -1 ? this->width : atlasWidth;
    this->atlasTileHeight = atlasHeight == -1 ? this->height : atlasHeight;
}

Texture::~Texture() {
    glDeleteTextures(1, &textureId);
}

void Texture::genTexture() {
    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::vector<GLfloat> Texture::generateFromPosition(unsigned int x, unsigned int y, int width, int height) {
    if (width == -1)
        width = this->atlasTileWidth;
    if (height == -1)
        height = this->atlasTileHeight;

    GLfloat reX = ((GLfloat) x * width) / this->width;
    GLfloat reY = ((GLfloat) y * height) / this->height;
    GLfloat newX = ((GLfloat) x * width + width) / this->width;
    GLfloat newY = ((GLfloat) y * height + height) / this->height;
    reX += 1.0 / this->width;
    reY += 1.0 / this->height;
    newX -= 1.0 / this->width;
    newY -= 1.0 / this->height;
    return {
        reX, reY, // 0
        reX, newY, // 1
        newX, newY, // 2
        newX, reY, // 3
    };
}

std::vector<GLfloat> Texture::generateFromPosition(const std::pair<unsigned int, unsigned int>& position, int width, int height) {
    return generateFromPosition(position.first, position.second, width, height);
}

} // namespace genesis
