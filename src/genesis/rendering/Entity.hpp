#pragma once

#include "Model.hpp"
#include "genesis/rendering/Renderable.hpp"
#include "glm/matrix.hpp"
#include "glm/vec3.hpp"
#include <iostream>
#include <memory>

namespace genesis {

class Collider;
/**
 * Entities are the simplest type of textured GameObject.
 * It has a position, optional rotation, and a Model.
 *
 * In-game movable entities with a state should inherit Entity.
 *
 * May be made abstract in the future
 */
class Entity : public Renderable {
private:
    std::shared_ptr<Model> model;

    glm::vec3 position;
    glm::vec3 rotation;
    float scale;

    glm::mat4 transMatrix;

protected:
    // TODO: Sort out your shit, Olivia
    void regenerateTransMatrix();

    Entity() = default;
public:
    Entity(const std::shared_ptr<Model>& model, glm::vec3 position, glm::vec3 rotation, float scale)
            : model(model), position(position), rotation(rotation), scale(scale) {
        regenerateTransMatrix();
    }
    Entity(const std::shared_ptr<Model>& model, glm::vec3 position) : Entity(model, position, glm::vec3{0, 0, 0}, 0) {}

    virtual void tick();
    void render() override;

    /**
     * Glorified `with` (python) alternative.
     * Calls regenerateTransMatrix() when the block is done iff the callback
     * returns true
     */
    void modify(const std::function<bool()>& callback) {
        if (callback()) {
            regenerateTransMatrix();
        }
    }

    glm::vec3& getPosition() {
        return position;
    }
    const glm::vec3& getPosition() const {
        return position;
    }

    glm::vec3& getRotation() {
        return rotation;
    }

    float& getScale() {
        return scale;
    }


};

} // namespace genesis
