#include "InputManager.hpp"
#include "GLFW/glfw3.h"
#include "genesis/core/Runner.hpp"
#include <iostream>
#include <stdexcept>

namespace genesis {

void InputManager::onKeyPressed(int key, int, int action, int mods) {
    std::string fwd = std::to_string(key) + std::to_string(mods);
    auto it = registeredKeys.find(fwd);
    if (it != registeredKeys.end()) {
        (*it).second(*this, action);
    }
}

bool InputManager::registerKeyCallback(int key, int mods, InputCallback callback) {
    if (callback == nullptr) {
        throw std::runtime_error("Cannot register a null callback");
    }
    std::string fwd = std::to_string(key) + std::to_string(mods);

    if (registeredKeys.find(fwd) != registeredKeys.end()) {
        // The key has already been mapped.
        return false;
    }
    this->registeredKeys.insert(std::make_pair(fwd, callback));
    return true;
}

void InputManager::onMousePressed(int button, int action, int mods) {
    // This is done purely for the sake of tracking whether the primary button
    // is pressed.
    // This is largely for tracking mouse-motion sensitive stuff, like previews
    // of drag actions.
    // Problem for the future tho
    // Could potentially expand to a vector or something if more keys need this
    // level of control
    // Need to take modifiers into account though.
    if (button == GLFW_MOUSE_BUTTON_1)
        this->isMouse1Pressed = action;
    double x, y;
    glfwGetCursorPos(this->runner.getRenderer().getWindow(), &x, &y);
    // And use the position here for something:tm:
    // TODO: for when tiling is done
}

void InputManager::onMouseMoved(double x, double y) {
    // TODO: drag or whatever
    // I guess
}

} // namespace genesis
