#pragma once

#include "genesis/rendering/Texture.hpp"

#include "stc/FntParser.hpp"

#include <map>
#include <optional>

namespace genesis {

class FontAtlas : public Texture {
public:
    /* Theoretically tested values for the entirety of unicode
    2 << 13;
    143859;
    */
    //static inline constexpr int DIMENSIONS = 512;
    //static inline constexpr int CHARACTERS = 256;

private:
    stc::FntParser::FntInfo font;

public:
    //explicit FontAtlas(const std::string& font = "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf");
    FontAtlas();

    std::optional<stc::FntParser::FntCharInfo> getCharacter(int chr) {
        if (font.characters.contains(chr))
            return font.characters.at(chr);
        return {};
    }

};

} // namespace genesis
