#include "WorldController.hpp"

#include "genesis/rendering/Constants.hpp"
#include "genesis/rendering/Entity.hpp"
#include "genesis/rendering/Model.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/rendering/Texture.hpp"
#include "genesis/rendering/environment/Chunk.hpp"

#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

namespace genesis {

WorldController::WorldController() : inputManager(*this), renderer(*this) {
    int result = renderer.initializeWindow();
    if (result != 0) {
        throw std::runtime_error("Initializing the window failed");
    }

    this->texturePack = std::make_shared<genesis::Texture>("images/programmer.png");
    auto chunk = std::make_shared<Chunk>(*this, -1, 0);
    renderer.objects.push_back(chunk);

    glfwSetWindowUserPointer(renderer.getWindow(), &inputManager);
    glfwSetKeyCallback(renderer.getWindow(), [](GLFWwindow* win, int key, int scanCode, int action, int mods) {
        ((InputManager*) glfwGetWindowUserPointer(win))->onKeyPressed(key, scanCode, action, mods);
    });
    glfwSetMouseButtonCallback(renderer.getWindow(), [](GLFWwindow* win, int button, int action, int mods) {
        ((InputManager*) glfwGetWindowUserPointer(win))->onMousePressed(button, action, mods);
    });
    glfwSetCursorPosCallback(renderer.getWindow(), [](GLFWwindow* win, double x, double y) {
        ((InputManager*) glfwGetWindowUserPointer(win))->onMouseMoved(x, y);
    });

    WorldController::INSTANCE = this;
}

void WorldController::runGame() {
    this->renderer.render();
    auto targetTime = std::chrono::duration<double, std::milli>(8.3);

    auto lastTime = std::chrono::high_resolution_clock::now();
    do {
        auto now = std::chrono::high_resolution_clock::now();
        delta = std::chrono::duration<double, std::ratio<1>>(now - lastTime).count();

        // TODO: figure out how to best design a loop that makes TPS
        // and FPS separate (... at least partially)
        // At least to the point where FPS != TPS by loop definition
        // Though might never be a problem. A certain degree of async
        // processing might avoid that being necessesary.
        inputManager.tick();

        renderer.tick();
        renderer.render();

        auto end = std::chrono::high_resolution_clock::now();
        lastTime = end;
        auto sleepFor = targetTime - (now - end);
        if (sleepFor > std::chrono::milliseconds(0))
            std::this_thread::sleep_for(sleepFor);
    } while (glfwWindowShouldClose(renderer.getWindow()) == 0);

    glfwTerminate();
}

} // namespace genesis
