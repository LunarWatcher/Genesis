#include "Menu.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/ui/Text.hpp"

namespace genesis {

MenuScene::MenuScene() {

    auto play = std::make_shared<TextModel>("Play", 200, 200, 1, glm::vec4{ 1.0, 0.0, 1.0, 1.0 });
    models.push_back(play);

}

void MenuScene::render() {
    Renderer& inst = Renderer::getInstance();

    auto ts = inst.getTextShader();
    auto fa = inst.getFontAtlas();

    ts->apply();
    fa->bind();

    for (auto model : models) {
        model->render();
    }

    fa->unbind();
    ts->stop();
}

void MenuScene::tick() {

}

}
