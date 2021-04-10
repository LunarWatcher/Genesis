#pragma once

#include "Model.hpp"
#include "genesis/rendering/Renderable.hpp"
#include "glm/matrix.hpp"
#include "glm/vec3.hpp"

namespace genesis {

class Entity : public Renderable {
private:
    std::shared_ptr<TexturedModel> model;
    glm::vec3 position;
    glm::vec3 rotation;
    float scale;

    glm::mat4 transMatrix;

protected:
    void regenerateTransMatrix();

public:
    Entity(std::shared_ptr<TexturedModel> model, glm::vec3 position, glm::vec3 rotation, float scale)
            : model(model), position(position), rotation(rotation), scale(scale) {
        regenerateTransMatrix();
    }
    Entity(std::shared_ptr<TexturedModel> model, glm::vec3 position) : Entity(model, position, glm::vec3{0, 0, 0}, 0) {}

    void render(DefaultShader& shader) override;
};

} // namespace genesis
