#include "Menu.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/ui/Text.hpp"
#include "spdlog/spdlog.h"

namespace genesis {

// MenuScene {{{
MenuScene::MenuScene() {
    auto uiController = std::make_shared<MenuController>();
    this->entityControllers.push_back(uiController);
}

void MenuScene::render() {
    Renderer& inst = Renderer::getInstance();

    auto ts = inst.getTextShader();
    auto fa = inst.getFontAtlas();

    ts->apply();
    fa->bind();

    for (auto& controller : this->entityControllers) {
        controller->render();
    }

    fa->unbind();
    ts->stop();
}

void MenuScene::tick() {
    for (auto& controller : this->entityControllers) {
        controller->tick();
    }
}

const std::vector<std::shared_ptr<EntityController>>& MenuScene::getEntityControllers() {
    return entityControllers;
}
// }}}
// MenuController {{{
MenuController::MenuController() {
    auto play = std::make_shared<TextEntity>("Play", 200, 200, 1, glm::vec4{ 1.0, 0.0, 1.0, 1.0 });
    play->ID = BTN_PLAY;

    entities.push_back(play);
}

void MenuController::tick() {
    for (auto& entity : entities) {
        entity->tick();
    }
}

bool MenuController::hasCollision(const std::shared_ptr<Rectangle> &collider) {
    for (auto& entity : entities) {
        if (entity->getCollider() != nullptr && entity->getCollider()->collidesWith(*collider, true)) {
            if (entity->ID == BTN_PLAY) {
                Renderer::getInstance().createGame();
            }
            return true;
        }
    }

    return false;
}
// }}}

}
