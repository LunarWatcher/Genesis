#pragma once

#include "genesis/rendering/Texture.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <optional>

namespace genesis {

typedef struct {
    int advanceX, advanceY, //
        bitmapWidth, bitmapHeight, //
        bitmapLeft, bitmapTop, //
        textureX, textureY;
} Character;

class FontAtlas : public Texture {
public:
    static inline constexpr int DIMENSIONS = 512;
    static inline constexpr int CHARACTERS = 128;

private:
    FT_Face face;
    std::map<wchar_t, Character> characterMap;

public:
    FontAtlas(const std::string& font = "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf");

    std::optional<Character> getCharacter(wchar_t chr) {
        if (characterMap.contains(chr))
            return characterMap.at(chr);
        return {};
    }

    std::vector<float> generateUVCoords(const Character& chr);
};

} // namespace genesis