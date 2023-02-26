#include "InputProcessor.hpp"

#include <stdexcept>

namespace genesis {

void InputProcessor::updateInput(const std::map<InputCode, int>& maps) {
    for (auto& [k, v] : maps) {
        registeredKeys[k](v);
    }
}

void InputProcessor::registerKey(int key, int mods, std::function<bool(int action)> callback) {
    InputCode code{key, mods};

    if (registeredKeys.contains(code)) {
        throw std::runtime_error("Keybind conflict for key " + std::to_string(key) + "[" + std::to_string(mods) + "]");
    }

    registeredKeys[code] = callback;
}

}
