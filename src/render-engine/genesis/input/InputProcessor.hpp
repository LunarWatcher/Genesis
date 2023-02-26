#pragma once

#include <string>
#include <map>
#include <functional>

namespace genesis {

struct InputCode {
    int key;
    int mods;
};

inline bool operator<(const InputCode& a, const InputCode& b) {
    return a.key < b.key && a.mods < b.mods;
}

class InputProcessor {
public:

    std::map<InputCode, std::function<bool(int action)> /* callback */> registeredKeys; 
    std::map<InputCode, int> pressed;
    InputProcessor() = default;
    virtual ~InputProcessor() = default;

    virtual void updateInput(const std::map<InputCode, int>& maps);

    void registerKey(int key, int mods, std::function<bool(int action)> callback);

    /* Event receivers {{{ */
    virtual bool onMouseMoved(double /* x */, double /* y */) { return false; }
    /* }}} */
};

}
