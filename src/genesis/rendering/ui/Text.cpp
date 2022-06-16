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
    float maxX = sourceX, maxY = sourceY;
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
            y -= font.lineHeight * scale;
            x = sourceX;
            continue;
        }

        // Look for a character
        auto characterData = Renderer::getInstance().getFontAtlas()->getCharacter(character);

        if (!characterData) {
            continue;
        }

        float xPos = x + characterData->xOffset * scale;
        float yPos = y + (font.base - characterData->height - characterData->yOffset) * scale; //+ (characterData->height + characterData->yOffset) * scale;

        float width = characterData->width * scale;
        float height = characterData->height * scale;

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
        x += characterData->xAdvance * scale;
    }
    Entity::position = glm::vec3{
        sourceX,
        minY,
        0 };
    this->collider->setDims(maxX - sourceX, maxY - minY);
    this->collider->update(*this);

    this->model->createVBO(0, 2, points);
    this->model->createVBO(1, 2, uv);

    this->model->vertices = points.size() / 2;
    regenerateTransMatrix();


}

void TextEntity::render() {
    model->render();
}

} // namespace genesis
