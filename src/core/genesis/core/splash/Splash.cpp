#include "Splash.hpp"
#include "genesis/context/Context.hpp"
#include "genesis/rendering/Renderer.hpp"

#include "genesis/core/menu/Menu.hpp"

namespace genesis {

SplashScene::SplashScene() : text("", 0, 0) {
}

void SplashScene::render() {
    auto textShader = Renderer::getInstance().getTextShader();
    textShader->apply();
    text.render();
    textShader->stop();

}

void SplashScene::tick() {
    if (GlobalCtx.loader.isLoading()) {
        text.setText(GlobalCtx.loader.getDescription());
    } else {
        Renderer::getInstance().transition(
            std::shared_ptr<MenuScene>()
        );
    }
}

}
