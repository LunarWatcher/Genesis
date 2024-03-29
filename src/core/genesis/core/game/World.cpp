#include "World.hpp"

#include "genesis/Context.hpp"
#include "genesis/core/game/generation/WorldGenerator.hpp"
#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Entity.hpp"
#include "genesis/rendering/Model.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/Texture.hpp"
#include "genesis/rendering/gl/Framebuffer.hpp"
#include "genesis/math/physics/Ray.hpp"

#include <chrono>
#include <memory>
#include <functional>
#include <iostream>
#include <thread>

namespace genesis {
World::World(int width, int height) : generator(std::make_shared<perlin::DumbGenerator>()), layers(MapLayers(width, height)) {

    registerKey(GLFW_KEY_W, [](const KeyPressInfo& data) {
        if (data.action != GLFW_PRESS) return false;
        Context::getInstance().camera->incrementPosition(
            0,
            10.0 * Context::getInstance().renderer->getDelta() * getScrollAcceleratorCoefficient(data.mods)
        );
        return true;
    });
    registerKey(GLFW_KEY_A, [](const KeyPressInfo& data) {
        if (data.action != GLFW_PRESS) return false;
        Context::getInstance().camera->incrementPosition(
            -10.0 * Context::getInstance().renderer->getDelta() * getScrollAcceleratorCoefficient(data.mods), 
            0
        );
        return true;
    });
    registerKey(GLFW_KEY_S, [](const KeyPressInfo& data) {
        if (data.action != GLFW_PRESS) return false;
        Context::getInstance().camera->incrementPosition(
            0,
            -10.0 * Context::getInstance().renderer->getDelta() * getScrollAcceleratorCoefficient(data.mods)
        );
        return true;
    });
    registerKey(GLFW_KEY_D, [](const KeyPressInfo& data) {
        if (data.action != GLFW_PRESS) return false;
        Context::getInstance().camera->incrementPosition(
            10.0 * Context::getInstance().renderer->getDelta() * getScrollAcceleratorCoefficient(data.mods), 
            0
        );
        return true;
    });
    //frame = std::make_shared<Framebuffer>(40, 40, Settings::instance->getInt("width") - 80, Settings::instance->getInt("height") - 80);

}

void World::tick() {
    this->creatures.tick(*this);
}

void World::render() {
    //frame->bind();
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_DEPTH_TEST);

    auto& inst = Context::getInstance();
    inst.textureShader->apply();
    inst.texturePack->bind();

    layers.render();

    this->creatures.render();

    inst.texturePack->unbind();
    inst.textureShader->stop();
    //frame->unbind();
    //auto shader = inst.getUIShader();
    //shader->apply();
    //frame->render();
    //shader->stop();

}

std::pair<std::pair<int, int>, std::pair<int, int>> World::convertToChunkSpace(int tileX, int tileZ) {
    return {
        {
            std::floor(tileX / Constants::Chunks::CHUNK_SIZE),
            std::floor(tileZ / Constants::Chunks::CHUNK_SIZE),
        },
        {
            tileX % Constants::Chunks::CHUNK_SIZE,
            tileZ % Constants::Chunks::CHUNK_SIZE
        }
    };
}

} // namespace genesis
