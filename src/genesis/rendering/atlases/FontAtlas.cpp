#include "FontAtlas.hpp"

#include "genesis/rendering/Renderer.hpp"

#include <iostream>

namespace genesis {

FontAtlas::FontAtlas(const std::string& font) {
    // TODO: Font config
    // TODO: Font portability
    if (FT_New_Face(Renderer::getInstance().getFontLibrary(), font.c_str(), 0, &face)) {
        std::cerr << "Failed to load font" << std::endl;
        throw std::runtime_error("Failed to load fonts");
    }
    FT_Set_Pixel_Sizes(face, 0, 12);
}

} // namespace genesis
