#include "InputProcessor.hpp"

#include <stdexcept>
#include <iostream>

namespace genesis {

InputProcessor::InputProcessor() {

}

void InputProcessor::updateInput(const std::map<std::string, int>& maps) {
    for (auto& [k, v] : maps) {
        if (v < 0) continue;
        if (registeredKeys.contains(k)) {
            registeredKeys[k](v);
        }
    }
}

void InputProcessor::registerKey(int key, int mods, std::function<bool(int action)> callback) {
    std::string keyID = createMapKey(key, mods);
    if (registeredKeys.contains(keyID)) {
        throw std::runtime_error("Keybind conflict for key " + std::to_string(key) + "[" + std::to_string(mods) + "]");
    }

    registeredKeys[keyID] = callback;
}

}
