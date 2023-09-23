#pragma once

#include <string>
#include <map>
#include <unordered_map>
#include <functional>

namespace genesis {

struct KeyPressInfo {
    int action;
    int mods;
};

class InputProcessor {
private:
    bool disabled = false;
    bool input = false;
public:
    std::unordered_map<std::string, std::function<bool(const KeyPressInfo& data)> /* callback */> registeredKeys; 

    InputProcessor();
    virtual ~InputProcessor() = default;

    virtual void updateInput(const std::map<std::string, KeyPressInfo>& maps);

    void registerKey(int key, std::function<bool(const KeyPressInfo&)> callback);
    void deregister(int key);

    /* Event receivers {{{ */
    virtual bool onMouseMoved(double /* x */, double /* y */) { return false; }
    /* }}} */

    static std::string createMapKey(int scanCode) {
        return std::to_string(scanCode);
    }
};


}
