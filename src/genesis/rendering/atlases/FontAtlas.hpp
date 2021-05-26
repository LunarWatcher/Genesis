#pragma once

#include "GL/gl.h"
#include "genesis/rendering/Texture.hpp"
#include <map>

namespace genesis {

class FontAtlas : public Texture {
private:
public:
    FontAtlas(const std::string& font = "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf");
};

} // namespace genesis
