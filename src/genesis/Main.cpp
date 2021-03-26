#include <iostream>
#include "rendering/RenderObject.hpp"
#include "rendering/Renderer.hpp"
#include "rendering/Texture.hpp"

int main() {
    genesis::Renderer renderer;
    int result = renderer.initializeWindow();
    if (result != 0) {
        return result;
    }
    std::vector<GLfloat> square = {
        -0.5f, 0.5f, 0.0,
        -0.5f, -0.5f, 0.0,
        0.5f, -0.5f, 0.0,
        0.5f, -0.5f, 0.0,
        0.5f, 0.5f, 0.0,
        -0.5f, 0.5f, 0.0
    };
    std::vector<GLfloat> uvCoords = {
        0, 0,
        1, 0,
        1, 1,
        0, 1
    };
    auto texture = std::make_shared<genesis::Texture>("images/test.png");
    auto object = std::make_shared<genesis::RenderObject>(square/*, uvCoords, texture*/);

    renderer.objects.push_back(object);
    renderer.renderBlocking();
}
