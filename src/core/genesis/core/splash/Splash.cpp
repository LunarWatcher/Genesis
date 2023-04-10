#include "Splash.hpp"
#include "genesis/Context.hpp"
#include "genesis/rendering/Renderer.hpp"

#include "genesis/core/menu/Menu.hpp"

namespace genesis {

SplashScene::SplashScene() : text("", 0, 0) {
}

void SplashScene::render() {
    auto textShader = Context::getInstance().textShader;
    textShader->apply();
    text.render();
    textShader->stop();

}

void SplashScene::tick() {
    if (Context::getInstance().dataLoader.isLoading()) {
        text.setText(Context::getInstance().dataLoader.getDescription());
    } else {
        Context::getInstance().renderer.transition(
            std::make_shared<MenuScene>()
        );
    }
}

}
