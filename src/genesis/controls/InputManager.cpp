#include "InputManager.hpp"
#include "genesis/core/Runner.hpp"
#include <iostream>
#include <stdexcept>

namespace genesis {

void InputManager::onKeyPressed(GLFWwindow*, int key, 
                                int, int action, int mods) {
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

}
