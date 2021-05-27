#pragma once

#include "genesis/rendering/Texture.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>

namespace genesis {

typedef struct {
    int advanceX, advanceY, //
        bitmapWidth, bitmapHeight, //
        bitmapLeft, bitmapTop, //
        textureX, textureY;
} Character;

class FontAtlas : public Texture {
private:
    FT_Face face;
    std::map<wchar_t, Character> characterMap;

public:
    FontAtlas(const std::string& font = "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf");
};

} // namespace genesis
