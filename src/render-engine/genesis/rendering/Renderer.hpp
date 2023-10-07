#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "genesis/rendering/Model.hpp"
#include "genesis/rendering/Renderable.hpp"

#include "genesis/rendering/flow/Scene.hpp"
#include "genesis/input/InputProcessor.hpp"

#include "spdlog/logger.h"
#include "spdlog/spdlog.h"

#include <iostream>
#include <memory>
#include <vector>
#include <type_traits>

//#include <ft2build.h>
//#include FT_FREETYPE_H

#ifdef API_DEBUG
// Used for debugging OpenGL API calls
// Super useful for backtracing invalid calls
inline void GLAPIENTRY MessageCallback(
    GLenum, GLenum type, GLuint id, GLenum severity, GLsizei, const GLchar* message, const void*) {
    if (std::string(message).find("will use VIDEO memory as the source") != std::string::npos) {
        // Silence verbose video memory warnings
        return;
    }
    switch (id) {
    // Useless or indecipherable messages
    case 131218:
        // Nvidia's "shader will be recompiled based on GL state": only appears once,
        // no resources on what it means or how to fix it. Should be fine to ignore.
        // real shame that this is the best answer though: https://stackoverflow.com/a/13201020/6296561
        // There's allegedly a state change triggering it, but like, where??
        // Fuck knows, but it's fine. It's a one-time change, won't have much of an impact

        break;
    default:
        std::cout << "GL CALLBACK: ";
        switch(type) {
        case GL_DEBUG_TYPE_ERROR:
            std::cout << "ERROR";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            std::cout << "DEPRECATED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            std::cout << "UNDEFINED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            std::cout << "PORTABILITY";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            std::cout << "PERFORMANCE";
            break;
        case GL_DEBUG_TYPE_OTHER:
            std::cout << "OTHER";
            break;
        }
        std::cout << " [";
        switch (severity){
        case GL_DEBUG_SEVERITY_LOW:
            std::cout << "LOW";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            std::cout << "MEDIUM";
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            std::cout << "HIGH";
            break;
        }
        std::cout << "] [ID=" << id << "] message = " << message << std::endl;
        break;
    }

}
#endif

namespace genesis {

namespace GLFWDebug {

// Don't think this needs to be enable-only; this has a lot of applications.
inline void GLFWCallback(int code, const char* error) {
    spdlog::error("GLFW error {}: {}", code, error);
}

}

class World;

class Renderer {
protected:
    static std::shared_ptr<spdlog::logger> logger;

    GLFWwindow* window;

    /**
     * Vector of active scenes.
     *
     * The definition of an active scene isn't just "a scene being rendered now",
     * but one that's used to operate the current set of scenes.
     *
     * For a full-focus settings screen while the game is running, or a full-focus
     * menu screen while the game is running, the the underlying game is still
     * considered active, even if it isn't updated.
     *
     * Essentially, suspended scenes are still considered active
     */
    std::vector<std::shared_ptr<Scene>> activeSceneStack;

    double delta;
    int frames;

    //FT_Library fontLibrary;

    // Scene management {{{
    int activeScene = 0;
    // }}}
    /* Input state management {{{*/
    std::map<int, KeyPressInfo> keyStates;
    /*}}}*/

    void initGame();

public:
    Renderer();
    virtual ~Renderer() = default;

    virtual void tick();
    virtual void render();

    void run();

    GLFWwindow* getWindow() {
        return window;
    }

    double getDelta() {
        return delta;
    }

    int getFps() {
        return frames;
    }

    auto getActiveScene() {
        return activeScene;
    }

    template <typename T>
    std::shared_ptr<T> getSceneByType() {
        for (auto& scene : this->activeSceneStack) {
            auto ptr = std::dynamic_pointer_cast<T>(scene);
            if (ptr) return ptr;
        }
        return nullptr;
    }

    const decltype(activeSceneStack)& getActiveSceneStack() { return activeSceneStack; }

    void transition(const std::shared_ptr<Scene>& scene);
    void add(const std::shared_ptr<Scene>& scene);
    void pop(const std::shared_ptr<Scene>& scene);

    void refreshDisplay();

};

} // namespace genesis
