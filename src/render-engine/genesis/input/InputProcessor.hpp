#pragma once

#include <string>
#include <map>
#include <unordered_map>
#include <functional>

namespace genesis {

class InputProcessor {
public:

    std::unordered_map<std::string, std::function<bool(int action)> /* callback */> registeredKeys; 

    InputProcessor();
    virtual ~InputProcessor() = default;

    virtual void updateInput(const std::map<std::string, int>& maps);

    void registerKey(int key, int mods, std::function<bool(int action)> callback);
    void deregister(int key, int mods);

    /* Event receivers {{{ */
    virtual bool onMouseMoved(double /* x */, double /* y */) { return false; }
    /* }}} */

    static std::string createMapKey(int scanCode, int mods) {
        return std::to_string(scanCode) + std::to_string(mods);
    }
};

}
