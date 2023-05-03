#pragma once

// there are no replacements, and I'm not going to implement anything myself.
// Windows insists on me using the Windows API, and that isn't happening. Linux is quiet, so that's fine.
// No replacements currently exist: https://stackoverflow.com/a/42946556/6296561
// and the recommendation is to uses platform implementations instead, but honestly, I don't really care.
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include "genesis/rendering/Model.hpp"
#include "genesis/rendering/Entity.hpp"

#include <codecvt>
#include <locale>
#include <string_view>


namespace genesis {

class TextEntity : public Entity {
private:
    static inline std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    glm::vec4 color;

    void regenerateVertices(const std::string_view& text, float x, float y, float scale);

public:
    TextEntity(
        const std::string_view& text,
        float x,
        float y,
        float scale = 1,
        const glm::vec4& color = {1, 0, 0, 1},
        decltype(ID) id = -1
    );

    void render() override;

    // Text setting
    // The ones involving position are gonna need to be altered if a matrix is used
    // instead.
    // Depends on how much text-related
    void setText(const std::string& text);
    void setText(const std::string_view& text);

};

} // namespace genesis
