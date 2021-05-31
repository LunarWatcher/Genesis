#include "Text.hpp"
#include "genesis/rendering/Renderer.hpp"

#include <iostream>

namespace genesis {

void TextModel::regenerateVertices(const std::string& text, float x, float y, float scale) {
    const float sourceX = x;
    std::wstring wide = converter.from_bytes(text);
    VertexArray points, uv;

    for (auto& character : wide) {
        auto characterData = Renderer::getInstance().getFontAtlas()->getCharacter(character);

        if (!characterData) {
            continue;
        }
        if (character == L'\n') {
            y -= (characterData->advanceY >> 6) * /*2.4 */ scale;
            x = sourceX;
            continue;
        }

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
        x += (characterData->advanceX >> 6) * scale;
    }

    createVBO(0, 2, points);
    this->vertices = points.size() / 2;

    createVBO(1, 2, uv);
}

void TextModel::render() {
    Model::render();
}

void TextModel::createVBO(unsigned int attribNumber, int coordSize, const VertexArray& data) {
    if (this->vbos.size() < attribNumber + 1) {
        Model::createVBO(attribNumber, coordSize, data);
    } else {
        auto vbo = this->vbos.at(attribNumber);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], mode);
        glVertexAttribPointer(attribNumber, coordSize, GL_FLOAT, false, 0, (void*) 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

} // namespace genesis
