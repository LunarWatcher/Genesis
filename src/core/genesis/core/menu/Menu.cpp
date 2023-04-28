#include "Menu.hpp"
#include "genesis/Context.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/ui/Text.hpp"
#include "genesis/math/physics/Ray.hpp"
#include "spdlog/spdlog.h"

#include "genesis/core/game/generation/WorldGenerator.hpp"

namespace genesis {

// MenuScene {{{
MenuScene::MenuScene() : Scene(true) {
    auto uiController = std::make_shared<MenuController>();
    this->entityControllers.push_back(uiController);

    registerKey(GLFW_MOUSE_BUTTON_1, 0, [](int action) {
        // TODO: check action when coc.nvim decides to start working again.
        // Fucking shit plugin
        double x = NAN, y = NAN;
        glfwGetCursorPos(Context::getInstance().renderer->getWindow(), &x, &y);

        // I suppose that in a real system, we'd need to detect release?
        // And then check if there's dragging or some shit like that
        // iDunno

        return Ray::traceClick({x, Settings::instance->getInt("height") - y},
            Ray::normalizeScreenCoords(x, y));

    });
}

void MenuScene::render() {
    auto ts = Context::getInstance().textShader;
    auto fa = Context::getInstance().fontAtlas;

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
                WorldGenerator::newWorld(
                    3,
                    3,
                    "The Great Roman Empire"
                );
            }
            return true;
        }
    }

    return false;
}
// }}}

}
