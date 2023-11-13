#include "Menu.hpp"
#include "genesis/Context.hpp"
#include "genesis/input/InputProcessor.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/ui/Text.hpp"
#include "genesis/math/physics/Ray.hpp"
#include "spdlog/spdlog.h"

#include "genesis/core/game/generation/WorldGenerator.hpp"

namespace genesis {

MenuScene::MenuScene() : Scene(true) {
    uiEntities.push_back(
        std::make_shared<TextEntity>("Play", 100, 200, 1, glm::vec4{ 1.0, 0.0, 1.0, 1.0 }, BTN_PLAY)
    );
    uiEntities.push_back(
        std::make_shared<TextEntity>(
            "Play", 
            500, 200,
            glm::vec4{59.0 / 255.0, 1.0, 157.0 / 255.0, 1.0},
            glm::vec2{10, 5},
            1,
            glm::vec4{ 0.0, 0.0, 0.0, 1.0 },
            BTN_PLAY
        )
    );


    registerKey(GLFW_MOUSE_BUTTON_1, [](const KeyPressInfo& data) {

        if (data.action != GLFW_RELEASE) {
            return false;
        }
        double x = NAN, y = NAN;
        glfwGetCursorPos(Context::getInstance().renderer->getWindow(), &x, &y);

        return Ray::traceClick(
            {x, Settings::instance->getInt("height") - y},
            Ray::normalizeScreenCoords(x, y)
        );

    });
}

void MenuScene::render() {
    auto ts = Context::getInstance().textShader;
    auto fa = Context::getInstance().fontAtlas;

    ts->apply();
    fa->bind();

    for (auto& uiComponent : uiEntities) {
        uiComponent->render();
    }

    fa->unbind();
    ts->stop();
}

void MenuScene::tick() {
    for (auto& uiComponent : uiEntities) {
        uiComponent->tick();
    }
}

bool MenuScene::checkMouseCollision(const glm::vec2& rawCoords, const glm::vec3&) {
    auto collider = Rectangle{rawCoords, glm::vec2(1.f, 1.f)};
    for (auto& entity : uiEntities) {
        if (entity->getCollider() != nullptr && entity->getCollider()->collidesWith(collider, true)) {

            if (entity->ID == BTN_PLAY) {
                WorldGenerator::newWorld(
                    32, 32,
                    "The Great Roman Empire"
                );
            }
            return true;
        }
    }
    return false;
}

}
