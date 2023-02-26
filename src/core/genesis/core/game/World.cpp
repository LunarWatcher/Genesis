#include "World.hpp"

#include "genesis/core/game/generation/WorldGenerator.hpp"
#include "genesis/core/game/entities/Colonist.hpp"
#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Entity.hpp"
#include "genesis/rendering/Model.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/Texture.hpp"
#include "genesis/rendering/environment/Chunk.hpp"
#include "genesis/world/PlayerCamp.hpp"
#include "genesis/math/physics/Ray.hpp"

#include <chrono>
#include <memory>
#include <functional>
#include <iostream>
#include <thread>

namespace genesis {
World::World() : generator(std::make_shared<perlin::DumbGenerator>()) {
    World::INSTANCE = this;
}

void World::tick() {
    for (auto& controller : this->entityControllers)
        controller->tick();
}

void World::render() {
    Renderer& inst = Renderer::getInstance();
    inst.getTextureShader()->apply();
    inst.getTexturePack()->bind();

    for (auto& chunk : this->chunks)
        chunk->render();

    for (auto& controller : this->entityControllers)
        controller->render();

    inst.getTexturePack()->unbind();
    inst.getTextureShader()->stop();
}

const std::vector<std::shared_ptr<EntityController>>& World::getEntityControllers() {
    return entityControllers;
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

//bool World::onKeyPressed(int key, int scanCode, int action, int mods) {
    //switch(key) {
    //case GLFW_KEY_W:
        //Renderer::getInstance().getCamera()->incrementPosition(0, 10.0 * Renderer::getInstance().getDelta());
    
        //return true;
    //case GLFW_KEY_A:
        //Renderer::getInstance().getCamera()->incrementPosition(-10.0 * Renderer::getInstance().getDelta(), 0);
        //return true;
    //case GLFW_KEY_S:
        //Renderer::getInstance().getCamera()->incrementPosition(0, -10.0 * Renderer::getInstance().getDelta());
        //return true;
    //case GLFW_KEY_D:
        //Renderer::getInstance().getCamera()->incrementPosition(10.0 * Renderer::getInstance().getDelta(), 0);
        //return true;
    //default:
        //break;
    //}
    //return false;
//}

//bool World::onMousePressed(int button, int action, int mods) {
    //if (mods == 0 && button == GLFW_MOUSE_BUTTON_1) {
        //// TODO: check action when coc.nvim decides to start working again.
        //// Fucking shit plugin
        //double x = NAN, y = NAN;
        //glfwGetCursorPos(Renderer::getInstance().getWindow(), &x, &y);

        //// I suppose that in a real system, we'd need to detect release?
        //// And then check if there's dragging or some shit like that
        //// iDunno

        //return Ray::traceClick({x, Settings::instance->getInt("height") - y},
            //Ray::normalizeScreenCoords(x, y));
    //}
    //return false;
//}

} // namespace genesis
