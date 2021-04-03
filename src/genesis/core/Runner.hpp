#pragma once

#include "genesis/rendering/Renderer.hpp"
#include "genesis/controls/InputManager.hpp"

namespace genesis {

class Runner {
private:
    static inline Runner* INSTANCE;
    Renderer renderer;
    InputManager inputManager;

    double delta;
public:
    Runner();
    
    /**
     * Manages the game loop
     */
    void runGame();
    
    double getDelta() { return delta; }
    static Runner* getRunner() {
        return Runner::INSTANCE;
    }
};

}
