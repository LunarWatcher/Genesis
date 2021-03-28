#pragma once

#include "genesis/rendering/Renderer.hpp"
#include "genesis/controls/InputManager.hpp"

namespace genesis {

class Runner {
private:
    Renderer renderer;
public:
    Runner();
    void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    void runGame();
};

}
