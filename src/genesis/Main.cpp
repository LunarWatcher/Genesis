#include <iostream>
#include "rendering/Model.hpp"
#include "rendering/Renderer.hpp"
#include "rendering/Texture.hpp"

int main() {
    genesis::Renderer renderer;
    int result = renderer.initializeWindow();
    if (result != 0) {
        return result;
    }
    std::vector<GLfloat> square = {
        -0.5f, 0.5f , 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f , -0.5f, 0.0f,
        0.5f , 0.5f , 0.0f 
    };
    std::vector<GLfloat> uvCoords = {
        0, 0,
        0, 1,
        1, 1,
        1, 0
    };
    std::vector<GLint> indices = {0, 1, 3, 3, 1, 2};
    auto texture = std::make_shared<genesis::Texture>("images/test.png");
    auto rawObject = std::make_shared<genesis::Model>(square, indices, uvCoords);
    auto object = std::make_shared<genesis::TexturedModel>(rawObject, texture);
    renderer.objects.push_back(object);
    renderer.renderBlocking();
}
