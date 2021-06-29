#include "EntityController.hpp"

namespace genesis {

void EntityController::render() {
    for (auto& entity : this->entities) {
        // TODO: implement render optimizations
        entity->render();
    }
}

void EntityController::addEntity(std::shared_ptr<Entity> entity) {
    this->entities.push_back(entity);
}

} // namespace genesis
