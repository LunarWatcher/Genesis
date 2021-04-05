#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <map>
#include <string>
#include <functional>

namespace genesis {

class Runner;
class InputManager {
public:
    /**
     * The callback only needs to get the action.
     * The scancode is essentially useless for my application 
     * (or at least from what I can tell about it, it is useless for this use case),
     * and the callback itself has a pre-defined set of keys just by the std::string map.
     * Or, to be specific, these aren't general callbacks, but have been explicitly
     * registered for one specific string.
     */
    typedef std::function<void(InputManager&, int action)> InputCallback;
private:
    // Might make sense to make this a List<Function<...>>
    /**
     * There's probably a way to optimize this with pure ints, but I'm not sure how to best do that. 
     * So instead, for the time being, the internal API exploits strings to concat keys and modifiers
     * to create unique maps for different keys.
     */
    std::map<std::string, InputCallback> registeredKeys;
    Runner& runner;
public:
    InputManager(Runner& runner) : runner(runner) {}

    // TODO: figure out how to get GLFW to also register altgr as a modifier
    void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);

    /**
     * @returns             Whether or not the callback was added
     *                      If false, this implies there's already a callback for
     *                      the given combination of keys and modifiers.
     *                      At this time, only one key callback is allowed because
     *                      I coulnd't be arsed to make a list when I probably
     *                      won't use it effectively - ever.
     */
    bool registerKeyCallback(int key, int mods, InputCallback callback);
    Runner& getRunner();
};

}
