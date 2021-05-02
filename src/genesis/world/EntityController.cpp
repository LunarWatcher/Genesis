#include "EntityController.hpp"

namespace genesis {

void EntityController::render(DefaultShader& shader) {
    for (auto& entity : this->controlled) {
        entity->render(shader);
    }
}

void EntityController::addEntity(std::shared_ptr<Entity> entity) {
    this->controlled.push_back(entity);
}

} // namespace genesis
