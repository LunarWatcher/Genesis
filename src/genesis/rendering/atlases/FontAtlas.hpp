#pragma once

#include "freetype/freetype.h"
#include "genesis/rendering/Texture.hpp"

namespace genesis {

class FontAtlas : public Texture {
private:
    FT_Face face;

public:
    FontAtlas(const std::string& font = "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf");
};

} // namespace genesis
