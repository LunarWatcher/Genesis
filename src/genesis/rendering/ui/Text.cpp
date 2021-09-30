#include "Text.hpp"
#include "genesis/rendering/Renderer.hpp"

#include <iostream>

namespace genesis {

void TextModel::regenerateVertices(const std::string& text, float x, float y, float scale) {
    // Cache variable to store the leftmost x for newline operations
    const float sourceX = x;

    // Convert the string. Utility for dealing with unicode
    // Purely future-compatible at this time, however. While unicode is supported
    // on paper, the entirety of unicode isn't loaded into memory.
    std::wstring wide = converter.from_bytes(text);

    // Raw data
    VertexArray points, uv;

    for (auto& character : wide) {
        // Look for a character
        auto characterData = Renderer::getInstance().getFontAtlas()->getCharacter(character);

        if (!characterData) {
            continue;
        }
        // Special handling: newlines
        // This is the only character to modify y and reset x atm.
        // That is gonna change when text wrapping is implemented
        if (character == L'\n') {
            y -= (characterData->advanceY >> 6) * scale;
            x = sourceX;
            continue;
        }

        // Only render characters with textures
        if (characterData->textureX != -1 && characterData->textureY != -1) {
            float xPos = x + characterData->bitmapLeft * scale;
            float yPos = y - (characterData->bitmapHeight - characterData->bitmapTop) * scale;

            float width = characterData->bitmapWidth * scale;
            float height = characterData->bitmapHeight * scale;

            // clang-format off
            points.insert(points.end(), {
                xPos, yPos + height,
                xPos, yPos,
                xPos + width, yPos + height,
                xPos + width, yPos + height,
                xPos, yPos,
                xPos + width, yPos,
            });
            std::vector<float> tmp = Renderer::getInstance().getFontAtlas()->generateUVCoords(*characterData);
            uv.insert(uv.end(), tmp.begin(), tmp.end());
            // clang-format on
        }
        // x is incremented either way, largely to enable spaces
        x += (characterData->advanceX >> 6) * scale;
    }

    this->model.createVBO(0, 2, points);
    this->model.createVBO(1, 2, uv);

    this->model.vertices = points.size() / 2;
}

void TextModel::render() {
    model.render();
}

} // namespace genesis
