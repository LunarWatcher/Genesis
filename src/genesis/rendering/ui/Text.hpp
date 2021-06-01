#pragma once

#include "genesis/rendering/Model.hpp"

#include <codecvt>
#include <locale>

namespace genesis {

class TextModel : public Model {
private:
    static inline std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    void regenerateVertices(const std::string& text, float x, float y, float scale);

public:
    TextModel(const std::string& text, float x, float y, float scale = 1) : Model() {
        mode = GL_DYNAMIC_DRAW;
        createVAO();
        regenerateVertices(text, x, y, scale);
        glBindVertexArray(0);
    }

    void render() override;

    void createVBO(unsigned int attribNumber, int coordSize, const VertexArray& data) override;
};

} // namespace genesis
