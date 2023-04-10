#include "Context.hpp"

namespace genesis {

Context::Context() {

}

void Context::initRendererDeps() {
    // TODO: This is stupid. Detach the camera from the global namespace. Make it a per-game or per-scene thing,
    // depending on context.
    this->camera = std::make_shared<Camera>();

    this->texturePack = std::make_shared<genesis::TextureAtlas>("images/programmer.png");

    this->textureShader = std::make_shared<DefaultShader>();
    // Not currently used. Also TODO: refactor
    //this->primitiveShader = std::make_shared<DefaultShader>("primitive");
    this->textShader = std::make_shared<TextShader>();
    this->uiShader = std::make_shared<UIShader>();
    this->fontAtlas = std::make_shared<FontAtlas>();
}

}
