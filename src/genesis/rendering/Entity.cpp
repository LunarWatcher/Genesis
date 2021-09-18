#include "Entity.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "genesis/math/physics/Collider.hpp"

namespace genesis {

void Entity::tick() {
}

void Entity::render() {
    regenerateTransMatrix();
    Renderer::getInstance().getTextureShader()->loadTransMatrix(this->transMatrix);
    model->render();
}

void Entity::regenerateTransMatrix() {
    // Create identity matrix
    transMatrix = glm::mat4{1.0f};
    // translate
    transMatrix = glm::translate(this->transMatrix, this->position);
    // Rotate
    transMatrix = glm::rotate(this->transMatrix, this->rotation.x, glm::vec3{1, 0, 0});
    transMatrix = glm::rotate(this->transMatrix, this->rotation.y, glm::vec3{0, 1, 0});
    transMatrix = glm::rotate(this->transMatrix, this->rotation.z, glm::vec3{0, 0, 1});
}

} // namespace genesis
