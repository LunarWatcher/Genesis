#include "Texture.hpp"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace genesis {

Texture::Texture(const std::string& file) {
    unsigned char* source = stbi_load(file.c_str(), &width, &height, &comp, STBI_rgb_alpha);

    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, source);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    stbi_image_free(source);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    glDeleteTextures(1, &textureId);
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
        width = this->width;
    if (height == -1)
        height = this->height;

    double reX = ((double) x * width) / this->width;
    double reY = ((double) y * height) / this->height;
    double newX = ((double) x * width + width) / this->width;
    double newY = ((double) y * height + height) / this->height;
    reX += 1.0 / this->width;
    reY += 1.0 / this->height;
    newX -= 1.0 / this->width;
    newY -= 1.0 / this->height;
    return {reX, reY, reX, newY, newX, newY, newX, reY};
}

} // namespace genesis
