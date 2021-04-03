#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace genesis {

class Runner;
class InputManager {
private:
    Runner& runner;
public:
    InputManager(Runner& runner) : runner(runner) {}
    
    void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
};

}
