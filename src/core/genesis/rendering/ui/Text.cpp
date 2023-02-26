#include "Text.hpp"
#include "genesis/math/physics/Rectangle.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/conf/Settings.hpp"

#include "spdlog/spdlog.h"

#include <iostream>

namespace genesis {

TextEntity::TextEntity(const std::string& text, float x, float y, float scale, const glm::vec4& color)
        : color(color), pos(x, y), scale(scale) {
    model = std::make_shared<Model>();
    initializeCollider(std::make_shared<Rectangle>(0, 0, 0, 0, 0));

    model->mode = GL_DYNAMIC_DRAW;
    model->createVAO();
    regenerateVertices(text, x, y, scale);
    glBindVertexArray(0);
}

void TextEntity::regenerateVertices(const std::string& text, float x, float y, float scale) {
    glBindVertexArray(model->vaoID);
    // Cache variable to store the leftmost x for newline operations
    const float sourceX = x;
    const float sourceY = y;
    float maxX = sourceX, maxY = sourceY;
    // This has to be included to make sure rectangles can expand south
    float minY = y;

    // Convert the string. Utility for dealing with unicode
    // Purely future-compatible at this time, however. While unicode is supported
    // on paper, the entirety of unicode isn't loaded into memory.
    std::wstring wide = converter.from_bytes(text);

    // Raw data
    VertexArray points, uv;

    const auto& font = Renderer::getInstance().getFontAtlas()->getFont();

    for (auto& character : wide) {
        // Special handling: newlines
        // This is the only character to modify y and reset x atm.
        // That is gonna change when text wrapping is implemented
        if (character == L'\n') {
            y -= (float) font.lineHeight * scale;
            x = sourceX;
            continue;
        }

        // Look for a character
        auto characterData = Renderer::getInstance().getFontAtlas()->getCharacter(character);

        if (!characterData) {
            continue;
        }

        float xPos = x + (float) characterData->xOffset * scale;
        float yPos = y + (float) (font.base - characterData->height - characterData->yOffset) * scale; //+ (characterData->height + characterData->yOffset) * scale;

        float width = (float) characterData->width * scale;
        float height = (float) characterData->height * scale;

        maxX = std::max(maxX, xPos + width);
        maxY = std::max(maxY, yPos + height);
        minY = std::min(minY, yPos);

        // clang-format off
        points.insert(points.end(), {
            xPos, yPos + height,
            xPos, yPos,
            xPos + width, yPos + height,
            xPos + width, yPos + height,
            xPos, yPos,
            xPos + width, yPos,
        });
        std::vector<float> tmp = characterData->uvCoordinates;
        uv.insert(uv.end(), tmp.begin(), tmp.end());
        // clang-format on

        // x is incremented either way, largely to enable spaces
        x += (float) characterData->xAdvance * scale;
    }
    Entity::position = glm::vec3{
        sourceX,
        minY,
        0 };
    this->collider->setDims(maxX - sourceX, maxY - minY);
    this->collider->update(position);

    // TODO: account for changing text after the fact.
    // With the current system, the buffer has to be smaller than
    // the initial text to work, which isn't stonks.
    // This is easily fixable, but requires some changes
    // to the underlying class.
    // Particularly, "createOrReallocate" has to be used.
    // glBufferSubData is NOT an option for this.
    this->model->createOrResizeVBO(0, 2, points);
    this->model->createOrResizeVBO(1, 2, uv);

    this->model->vertices = static_cast<GLsizei>(points.size()) / 2;
    regenerateTransMatrix();
}

void TextEntity::render() {
    model->render();
}

void TextEntity::setText(const std::string& newText) {
    regenerateVertices(newText, pos.x, pos.y, scale);
}

} // namespace genesis
