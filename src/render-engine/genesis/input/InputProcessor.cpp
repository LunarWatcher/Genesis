#include "InputProcessor.hpp"

#include <stdexcept>
#include <iostream>

namespace genesis {

InputProcessor::InputProcessor() {

}

void InputProcessor::updateInput(const std::map<std::string, KeyPressInfo>& maps) {
    for (auto& [key, data] : maps) {
        if (data.action < 0) continue;
        if (registeredKeys.contains(key)) {
            registeredKeys[key](data);
        }
    }
}

void InputProcessor::registerKey(int key, std::function<bool(const KeyPressInfo&)> callback) {
    std::string keyID = createMapKey(key);
    if (registeredKeys.contains(keyID)) {
        throw std::runtime_error("Keybind conflict for key " + std::to_string(key));
    }

    registeredKeys[keyID] = callback;
}

void InputProcessor::deregister(int key) {
    std::string keyID = createMapKey(key);
    if (auto it = registeredKeys.find(keyID); it != registeredKeys.end()) {
        registeredKeys.erase(it);
    }
}

}
