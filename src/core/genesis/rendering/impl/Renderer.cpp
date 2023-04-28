#include "Renderer.hpp"
#include "genesis/rendering/Renderer.hpp"

#include "genesis/Context.hpp"

namespace genesis {

void GameRenderer::tick() {
    Renderer::tick();
}

void GameRenderer::render() {
    // TODO: set up a system to allow scenes to define these.
    // Though I'm not entirely sure if that's even necessary.
    // A few bits are tied to the camera class, but I'm not
    // sure if that's used elsewhere.
    // if it is, we may need to hook up a system that exposes
    // the currently rendered scene in a pointer or something.
    // It's already a pointer, so it's a fairly cheap operation.
    //
    // Just use some common sense though.
    // Why??
    Context::getInstance().camera->regenerateCameraMatrix();
    auto& textureShader = Context::getInstance().textureShader;
    textureShader->apply();
    textureShader->loadViewMatrix(Context::getInstance().camera->getViewMatrix());
    
    Renderer::render();
}

}
