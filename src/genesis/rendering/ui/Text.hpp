#pragma once

#include "genesis/rendering/Entity.hpp"

#include <codecvt>
#include <locale>

namespace genesis {

class TextModel : public Entity {
private:
    static inline std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    glm::vec4 color;
    glm::mat4 position;

    void regenerateVertices(const std::string& text, float x, float y, float scale);

public:
    TextModel(const std::string& text, float x, float y, float scale = 1, const glm::vec4& color = {1, 0, 0, 1})
            : Entity(), color(color) {
        renderMode = GL_DYNAMIC_DRAW;
        createVAO();
        regenerateVertices(text, x, y, scale);
        glBindVertexArray(0);
    }

    void render() override;

    void createVBO(unsigned int attribNumber, int coordSize, const VertexArray& data) override;

    // Text setting
    // The ones involving position are gonna need to be altered if a matrix is used
    // instead.
    // Depends on how much text-related
    void setText(const std::string& text);
    void setText(const std::string& text, float x, float y);
    void setText(const std::string& text, float x, float y, float scale);
};

} // namespace genesis
