#include "EntityController.hpp"

#include <memory>
#include "genesis/math/physics/Rectangle.hpp"

namespace genesis {

void EntityController::render() {
    for (auto& entity : this->entities) {
        // TODO: implement render optimizations
        entity->render();
    }
}

void EntityController::addEntity(std::shared_ptr<Entity> entity) {
    this->entities.push_back(entity);
    entity->modify([&]() {
        //entity->initializeCollider(std::make_shared<Rectangle>(0, 0, 1, 1));
        return true;
    });
}

} // namespace genesis
