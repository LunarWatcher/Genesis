#include "PhysicsWorld.hpp"
#include "genesis/rendering/Renderer.hpp"

namespace genesis {

void PhysicsWorld::registerControllers(int scene, const std::vector<std::shared_ptr<PhysicsController>>& controllers) {
    this->stageControllerMap[scene] = controllers;
}

void PhysicsWorld::tick() {
    for (auto& controller : stageControllerMap.at(Renderer::getInstance().getActiveScene())) {
        controller->tick();
    }
}

void PhysicsWorld::clickElement(double x, double y) {
    glm::vec2 worldCoords = Renderer::getInstance().getCamera()->convertToWorld(x, y);
    for (auto& controller : stageControllerMap.at(Renderer::getInstance().getActiveScene())) {
        if (controller->hasCollision(worldCoords)) {
            std::cout << "You've sunk my battleship" << std::endl;
            break;
        }
    }

}

}
