#include "DebugScene.hpp"

#include "genesis/rendering/Renderer.hpp"

namespace genesis {

void DebugScene::render() {
    if (perspectivePrims.empty() && orthoPrims.empty()) {
        return;
    }
    auto& ren = Renderer::getInstance();

    auto primShader = ren.getPrimitiveShader();
    primShader->apply();
    primShader->loadViewMatrix(ren.getCamera()->getViewMatrix());

    primShader->loadProjectionMatrix(ren.getCamera()->getOrthoMatrix());
    for (auto& p : orthoPrims) {
        p->render();
    }

    primShader->loadProjectionMatrix(ren.getCamera()->getPerspectiveMatrix());
    for (auto& p : perspectivePrims) {
        p->render();
    }
    primShader->stop();

}

void DebugScene::debugRect(const std::shared_ptr<Rectangle>& collider) {
    this->orthoPrims.push_back(std::make_shared<Primitive>(
        collider->getX(), collider->getY(), collider->getZ(),
        collider->getWidth(), collider->getHeight()
    ));
}

}
