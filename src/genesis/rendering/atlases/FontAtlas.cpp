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
    FT_Face face; // NOLINT
    if (FT_New_Face(Renderer::getInstance().getFontLibrary(), font.c_str(), 0, &face)) {
        throw std::runtime_error("Freetype died (0002)");
    }
    glActiveTexture(GL_TEXTURE0);
    FT_Set_Pixel_Sizes(face, 0, 48);
    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // GL_ALPHA was apparently deprecated in 4.0 (https://stackoverflow.com/a/15618571/6296561),
    // and doesn't seem to work.
    // Instead, the iamge data is stored in the red channel, which is re-converted to alpha
    // levels by the shaders.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, DIMENSIONS, DIMENSIONS, //
        0, GL_RED, GL_UNSIGNED_BYTE, 0);

    int x = 0, y = 0;
    unsigned int currRowHeight = 0;

    // 32 is the first printable character in the ASCII set.
    for (int i = 32; i < CHARACTERS; ++i) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            // No glyph found
            continue;
        }
        bool hasDimensions = face->glyph->bitmap.width != 0 && face->glyph->bitmap.rows != 0;

        if (x + face->glyph->bitmap.width > DIMENSIONS) {
            x = 0;
            y += currRowHeight;
            height += currRowHeight;
            currRowHeight = 0;
            if (y > DIMENSIONS) {
                throw std::runtime_error("0003: FontAtlas exhausted");
            }
        }

        auto mChar = wchar_t(i);
        // there are still some characters we do save.
        this->characterMap[mChar] = Character{
            face->glyph->advance.x, //
            face->glyph->advance.y, //
#ifndef _WIN32
            face->glyph->bitmap.width, //
            face->glyph->bitmap.rows, //
#else
            // Fuck you Windows
            static_cast<int>(face->glyph->bitmap.width),
            static_cast<int>(face->glyph->bitmap.rows),
#endif
            face->glyph->bitmap_left, //
            face->glyph->bitmap_top, //
            hasDimensions ? x : -1, hasDimensions ? y : -1 //
        };

        if (hasDimensions) {
            glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED,
                GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
            // Ony modify the coords if we actually have a dimension
            x += face->glyph->bitmap.width + 1;
            width += face->glyph->bitmap.width + 1;
            currRowHeight = std::max(currRowHeight, face->glyph->bitmap.rows);
        }
    }
    this->characterMap[L'\n'] = Character{0, face->size->metrics.height, 0, 0, 0, 0, -1, -1};

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unbind();

    // Free the font face
    FT_Done_Face(face);
}

std::vector<float> FontAtlas::generateUVCoords(const Character& chr) {
    float x = chr.textureX;
    float y = chr.textureY;
    float width = chr.bitmapWidth;
    float height = chr.bitmapHeight;

    float reX = ((float) x) / DIMENSIONS;
    float reY = ((float) y) / DIMENSIONS;
    float newX = ((float) x + width) / DIMENSIONS;
    float newY = ((float) y + height) / DIMENSIONS;
    // reX += 1.0 / DIMENSIONS;
    // reY += 1.0 / DIMENSIONS;
    // newX -= 1.0 / DIMENSIONS;
    // newY -= 1.0 / DIMENSIONS;

    return {
        reX, reY, // 0
        reX, newY, // 1
        newX, reY, // 3
        newX, reY, // 3
        reX, newY, // 1
        newX, newY, // 2
    };
}

} // namespace genesis
