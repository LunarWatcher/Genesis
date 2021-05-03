#include "EntityController.hpp"

namespace genesis {

void EntityController::render() {
    for (auto& entity : this->controlled) {
        entity->render();
    }
}

void EntityController::addEntity(std::shared_ptr<Entity> entity) {
    this->controlled.push_back(entity);
}

} // namespace genesis
