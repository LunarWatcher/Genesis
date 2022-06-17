#include "InputManager.hpp"
#include "GLFW/glfw3.h"
#include "genesis/rendering/Renderer.hpp"
#include <iostream>
#include <stdexcept>

namespace genesis {

void InputManager::onKeyPressed(int key, int, int action, int mods) {
    if (action == GLFW_REPEAT) {
        return;
    }
    std::string fwd = std::to_string(key) + std::to_string(mods);
    keys[fwd] = action == GLFW_PRESS;
}

bool InputManager::registerKeyCallback(int key, int mods, const InputCallback& callback) {
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
    // we can do substantially better, but for now, we just screw modifiers
    if (mods != 0) return;
    // This is done purely for the sake of tracking whether the primary button
    // is pressed.
    // This is largely for tracking mouse-motion sensitive stuff, like previews
    // of drag actions.
    // Problem for the future tho (fuck you past me, write better comments)
    // Could potentially expand to a vector or something if more keys need this
    // level of control
    // Need to take modifiers into account though.
    if (button == GLFW_MOUSE_BUTTON_1)
        this->isMouse1Pressed = action;

    double x = NAN, y = NAN;
    glfwGetCursorPos(Renderer::getInstance().getWindow(), &x, &y);

    // I suppose that in a real system, we'd need to detect release?
    // And then check if there's dragging or some shit like that
    // iDunno
    Renderer::getInstance().getPhysicsEngine()->clickElement(x, y);
}

void InputManager::onMouseMoved(double, double) {
    // TODO: drag or whatever
    // I guess
}

void InputManager::tick() {
    for (auto& [key, callback] : registeredKeys) {
        auto it = keys.find(key);
        if (it != keys.end()) {
            auto& pair = *it;
            if (pair.second >= 0) {
                bool result = callback(*this, pair.second);

                if (pair.second == 0 || result)
                    pair.second = -1;
            }
        }
    }
}

} // namespace genesis
