#include "InputProcessor.hpp"

#include <stdexcept>
#include <iostream>

namespace genesis {

InputProcessor::InputProcessor() {

}

void InputProcessor::updateInput(const std::map<int, KeyPressInfo>& maps) {
    if (disabled) {
        return;
    }
    for (auto& [key, data] : maps) {
        if (data.action < 0) continue;
        if (registeredKeys.contains(key)) {
            registeredKeys[key](data);
        }
    }
}

void InputProcessor::registerKey(int key, std::function<bool(const KeyPressInfo&)> callback) {
    if (registeredKeys.contains(key)) {
        throw std::runtime_error("Keybind conflict for key " + std::to_string(key));
    }

    registeredKeys[key] = callback;
}

void InputProcessor::deregister(int key) {
    if (auto it = registeredKeys.find(key); it != registeredKeys.end()) {
        registeredKeys.erase(it);
    }
}

}
