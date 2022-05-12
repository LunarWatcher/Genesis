#include "Primitive.hpp"

namespace genesis {

Primitive::Primitive(float x, float y, float z, float width, float height)
    : Entity(std::make_shared<Model>(
        std::vector<GLfloat>{
            0.0f, height, 0.0f,
            0.0f, 0.0f, 0.0f,
            width, 0.0f, 0.0f,
            width, height, 0.0f
        },
        [](Model* m) {
            m->setRenderType(GL_LINE_LOOP);

            m->bindIndexBuffer({
                0, 1, 2, 3
            });
            m->createVBO(1, 4, {
                0, 0, 0, 1,
                0, 0, 0, 1,
                0, 0, 0, 1,
                0, 0, 0, 1,
            });
        }
    ), glm::vec3(x, y, z)) {
    regenerateTransMatrix();
}

}
