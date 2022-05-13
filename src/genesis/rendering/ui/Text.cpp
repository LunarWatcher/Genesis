#include "Text.hpp"
#include "genesis/math/physics/Ray.hpp"
#include "genesis/math/physics/Rectangle.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/conf/Settings.hpp"

#include "genesis/rendering/debug/DebugScene.hpp"

#include "spdlog/spdlog.h"

#include <iostream>

namespace genesis {

TextEntity::TextEntity(const std::string& text, float x, float y, float scale, const glm::vec4& color)
        : color(color) {
    model = std::make_shared<Model>();
    initializeCollider(std::make_shared<Rectangle>(0, 0, 0, 0, 0));

    model->mode = GL_DYNAMIC_DRAW;
    model->createVAO();
    regenerateVertices(text, x, y, scale);
    glBindVertexArray(0);
}

void TextEntity::regenerateVertices(const std::string& text, float x, float y, float scale) {
    // Cache variable to store the leftmost x for newline operations
    const float sourceX = x;
    const float sourceY = y;
    float firstLineOffset = 9999;
    float maxX = sourceX, maxY = sourceY;

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
            if (points.empty()) {
                y -= characterData->bitmapHeight;
            }
            float xPos = x + characterData->bitmapLeft * scale;
            float yPos = y - (characterData->bitmapHeight - characterData->bitmapTop) * scale;

            float width = characterData->bitmapWidth * scale;
            float height = characterData->bitmapHeight * scale;

            maxX = std::max(maxX, xPos + width);
            maxY = std::max(maxY, yPos + height);

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
    Entity::position = glm::vec3{
        sourceX,
        y,
        //sourceX * 2.0 / Settings::instance->getInt("width") - 1,
        //1.0 - (sourceY + firstLineOffset) * 2.0 / Settings::instance->getInt("height"),
        0 };
    this->collider->setDims(maxX - sourceX, maxY - y);
    this->collider->update(*this);

    this->model->createVBO(0, 2, points);
    this->model->createVBO(1, 2, uv);

    this->model->vertices = points.size() / 2;
    regenerateTransMatrix();

    //Renderer::getInstance().getDebugScene()->debugRect(
        //std::static_pointer_cast<Rectangle>(this->collider)
    //);
}

void TextEntity::render() {
    model->render();
}

} // namespace genesis
