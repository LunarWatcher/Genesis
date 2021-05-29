#include "FontAtlas.hpp"

#include "GL/glew.h"

#include "genesis/rendering/Renderer.hpp"

#include <algorithm>
#include <codecvt>
#include <iostream>
#include <locale>
#include <string>

namespace genesis {

FontAtlas::FontAtlas(const std::string& font) {
    if (FT_New_Face(Renderer::getInstance().getFontLibrary(), font.c_str(), 0, &this->face)) {
        throw std::runtime_error("Freetype died (0002)");
    }
    FT_Set_Pixel_Sizes(this->face, 0, 48);
    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, DIMENSIONS, DIMENSIONS, //
        0, GL_RED, GL_UNSIGNED_BYTE, 0);
    // std::string x = "\uFDFD";
    // std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    // std::wstring wide = converter.from_bytes(x);

    int x = 0, y = 0;
    unsigned int currRowHeight = 0;

    // 32 is the first printable character in the ASCII set.
    for (int i = 32; i < CHARACTERS; ++i) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER) || face->glyph->bitmap.width == 0 || face->glyph->bitmap.rows == 0) {
            // No glyph found
            continue;
        }
        if (x + face->glyph->bitmap.width > DIMENSIONS) {
            x = 0;
            y += currRowHeight;
            currRowHeight = 0;
        }

        glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED,
            GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        wchar_t mChar = wchar_t(i);
        this->characterMap[mChar] = Character{
            //
            face->glyph->advance.x, //
            face->glyph->advance.y, //
            face->glyph->bitmap.width, //
            face->glyph->bitmap.rows, //
            face->glyph->bitmap_left, //
            face->glyph->bitmap_top, //
            x, y //
        };
        x += face->glyph->bitmap.width;
        currRowHeight = std::max(currRowHeight, face->glyph->bitmap.rows);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unbind();
}

std::vector<float> FontAtlas::generateUVCoords(const Character& chr) {
    return {
        double(chr.textureX) / DIMENSIONS,
        double(chr.textureY + chr.bitmapHeight) / DIMENSIONS,
        double(chr.textureX) / DIMENSIONS,
        double(chr.textureY) / DIMENSIONS,
        double(chr.textureX + chr.bitmapWidth) / DIMENSIONS,
        double(chr.textureY) / DIMENSIONS,
        double(chr.textureX) / DIMENSIONS,
        double(chr.textureY + chr.bitmapHeight) / DIMENSIONS,
        double(chr.textureX + chr.bitmapWidth) / DIMENSIONS,
        double(chr.textureY) / DIMENSIONS,
        double(chr.textureX + chr.bitmapWidth) / DIMENSIONS,
        double(chr.textureY + chr.bitmapHeight) / DIMENSIONS,
    };
}

} // namespace genesis
