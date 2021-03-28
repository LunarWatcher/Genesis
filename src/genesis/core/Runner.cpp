#include "Runner.hpp"

#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Entity.hpp"
#include "genesis/rendering/Model.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/Texture.hpp"

#include <functional>
#include <iostream>

namespace genesis {

Runner::Runner() {
    int result = renderer.initializeWindow();
    if (result != 0) {
        throw std::runtime_error("Initializing the window failed");
    }

    std::vector<GLint> indices = {0, 1, 3, 3, 1, 2};
    auto texture = std::make_shared<genesis::Texture>("images/test.png");
    auto rawObject = std::make_shared<genesis::Model>(genesis::Constants::square, indices, texture->generateFromPosition(0, 0, 128, 128));
    auto object = std::make_shared<genesis::TexturedModel>(rawObject, texture);
    auto entity = std::make_shared<genesis::Entity>(object, glm::vec3{0, -1, -3});
    renderer.objects.push_back(entity);

    glfwSetWindowUserPointer(renderer.getWindow(), this);
    glfwSetKeyCallback(renderer.getWindow(), [](GLFWwindow* win, int key, int scanCode, int action, int mods) {
        ((Runner*) glfwGetWindowUserPointer(win))->onKeyPressed(win, key, scanCode, action, mods);
    });
}

void Runner::onKeyPressed(GLFWwindow *window, int key, int scancode, int action, int mods) {
    std::cout << key << std::endl;
}

void Runner::runGame() {
    // TODO: make this function useful
    this->renderer.renderBlocking();
}

}
