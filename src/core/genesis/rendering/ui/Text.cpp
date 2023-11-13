#include "Text.hpp"
#include "genesis/math/physics/Rectangle.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/conf/Settings.hpp"
#include "genesis/Context.hpp"

#include "spdlog/spdlog.h"

#include <iostream>

namespace genesis {

TextEntity::TextEntity(
    const std::string_view& text,
    float x,
    float y,
    float scale,
    const glm::vec4& color,
    long long id
)
        : Entity(nullptr, glm::vec3(x, y, 0), glm::vec3(0, 0, 0), scale, id),
        color(color) {
    model = std::make_shared<Model>();
    initializeCollider(std::make_shared<Rectangle>(0, 0, 0, 0, 0));

    model->mode = GL_DYNAMIC_DRAW;
    model->createVAO();
    regenerateVertices(text, x, y, scale);
    glBindVertexArray(0);
}

TextEntity::TextEntity(
    const std::string_view& text,
    float x,
    float y,
    const glm::vec4& backgroundColour,
    const glm::vec2& padding,
    float scale,
    const glm::vec4& color,
    decltype(ID) id
)
        : Entity(nullptr, glm::vec3(x, y, 0), glm::vec3(0, 0, 0), scale, id),
        color(color), backgroundColour(backgroundColour), padding(padding) {
    model = std::make_shared<Model>();
    initializeCollider(std::make_shared<Rectangle>(0, 0, 0, 0, 0));

    model->mode = GL_DYNAMIC_DRAW;
    model->createVAO();
    regenerateVertices(text, x, y, scale);
    glBindVertexArray(0);
}

void TextEntity::regenerateVertices(const std::string_view& text, float x, float y, float scale) {

    glBindVertexArray(model->vaoID);
    // Cache variable to store the leftmost x for newline operations
    const float sourceX = x;
    const float sourceY = y;
    float maxX = sourceX, maxY = sourceY;
    // This has to be included to make sure rectangles can expand south
    float minY = y;
    float minX = sourceX;

    // Convert the string. Utility for dealing with unicode
    // Purely future-compatible at this time, however. While unicode is supported
    // on paper, the entirety of unicode isn't loaded into memory.

    // Raw data
    VertexArray points, uv;

    const auto& font = Context::getInstance().fontAtlas->getFont();

    for (auto& character : text) {
        // Special handling: newlines
        // This is the only character to modify y and reset x atm.
        // That is gonna change when text wrapping is implemented
        if (character == L'\n') {
            y -= (float) font.lineHeight * scale;
            x = sourceX;
            continue;
        }

        // Look for a character
        auto characterData = Context::getInstance().fontAtlas->getCharacter(character);

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

        points.insert(points.end(), {
            xPos, yPos + height, 0.f,
            xPos, yPos, 0.f,
            xPos + width, yPos + height, 0.f,
            xPos + width, yPos + height, 0.f,
            xPos, yPos, 0.f,
            xPos + width, yPos, 0.f,
        });
        std::vector<float> tmp = characterData->uvCoordinates;
        uv.insert(uv.end(), tmp.begin(), tmp.end());

        // x is incremented either way, largely to enable spaces
        x += (float) characterData->xAdvance * scale;
    }

    if (backgroundColour.has_value()) {
        auto padding = this->padding.value_or(glm::vec2{10, 5});
        points.insert(points.end(), {
            minX - padding.x, maxY + padding.y, -0.001f,
            minX - padding.x, minY - padding.y, -0.001f,
            maxX + padding.x, maxY + padding.y, -0.001f,
            maxX + padding.x, maxY + padding.y, -0.001f,
            minX - padding.x, minY - padding.y, -0.001f,
            maxX + padding.x, minY - padding.y, -0.001f,
        });
        uv.insert(uv.end(), {
            -1, -1,
            -1, -1,
            -1, -1,
            -1, -1,
            -1, -1,
            -1, -1,
        });
        minX -= padding.x;
        minY -= padding.y;
        maxX += padding.x;
        maxY += padding.y;
    }

    Entity::position = glm::vec3{
        minX,
        minY,
        0 };
    this->collider->setDims(maxX - minX, maxY - minY);
    this->collider->update(position);

    // TODO: account for changing text after the fact.
    // With the current system, the buffer has to be smaller than
    // the initial text to work, which isn't stonks.
    // This is easily fixable, but requires some changes
    // to the underlying class.
    // Particularly, "createOrReallocate" has to be used.
    // glBufferSubData is NOT an option for this.
    this->model->createOrResizeVBO(0, 3, points);
    this->model->createOrResizeVBO(1, 2, uv);

    this->model->vertices = static_cast<GLsizei>(points.size()) / 2;
    regenerateTransMatrix();
}

void TextEntity::render() {
    auto currShader = static_cast<TextShader*>(Shader::getActive());
    currShader->loadTextColor(color);
    if (backgroundColour.has_value()) {
        currShader->loadBackgroundColour(*backgroundColour);
    }
    model->render();
}

void TextEntity::setText(const std::string& newText) {
    regenerateVertices(newText, position.x, position.y, scale);
}

void TextEntity::setText(const std::string_view& newText) {
    regenerateVertices(newText, position.x, position.y, scale);
}

} // namespace genesis
