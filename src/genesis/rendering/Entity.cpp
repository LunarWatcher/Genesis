#include "Entity.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace genesis {

void Entity::render(DefaultShader& shader) {
    regenerateTransMatrix();
    shader.loadTransMatrix(this->transMatrix);
    model->render(shader);
}

void Entity::regenerateTransMatrix() {
    // Create identity matrix
    transMatrix = glm::mat4{1.0f};
    transMatrix = glm::translate(this->transMatrix, this->position);
    transMatrix = glm::rotate(this->transMatrix, this->rotation.x, glm::vec3{1, 0, 0});
    transMatrix = glm::rotate(this->transMatrix, this->rotation.y, glm::vec3{0, 1, 0});
    transMatrix = glm::rotate(this->transMatrix, this->rotation.z, glm::vec3{0, 0, 1});
}



}
