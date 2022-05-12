#include "Primitive.hpp"

namespace genesis {

Primitive::Primitive(float x, float y, float z, float width, float height)
    : Entity(std::make_shared<Model>(
        std::vector<GLfloat>{
            x, y + height, z,
            x, y, z,
            x + width, y, z,
            x + width, y + height, z
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
