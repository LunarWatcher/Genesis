#pragma once

#include <optional>
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
public:
    using KeyCallback = std::function<bool(const KeyPressInfo& data)>;
    using CharCallback = std::function<bool(int character)>;
private:
    bool disabled = false;
public:
    std::unordered_map<int,  KeyCallback> registeredKeys; 

    InputProcessor();
    virtual ~InputProcessor() = default;

    virtual void updateInput(const std::map<int, KeyPressInfo>& maps);

    void registerKey(int key, KeyCallback callback);
    void deregister(int key);

    /* Event receivers {{{ */
    virtual bool onMouseMoved(double /* x */, double /* y */) { return false; }
    /* }}} */
};

}
