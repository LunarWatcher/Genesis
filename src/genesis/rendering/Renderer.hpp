#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Entity.hpp"
#include "Renderable.hpp"

#include "genesis/rendering/atlases/FontAtlas.hpp"
#include "genesis/rendering/atlases/WorldTexture.hpp"
#include "genesis/rendering/flow/Scene.hpp"
#include "genesis/rendering/particles/ParticleEmitter.hpp"
#include "genesis/rendering/shaders/ParticleShader.hpp"
#include "genesis/rendering/shaders/TextShader.hpp"
#include "genesis/rendering/ui/Text.hpp"
#include "genesis/rendering/view/Camera.hpp"

#include "genesis/math/physics/PhysicsWorld.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <type_traits>

#include <spdlog/spdlog.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#ifdef API_DEBUG
// Used for debugging OpenGL API calls
// Super useful for backtracing invalid calls
inline void GLAPIENTRY MessageCallback(
    GLenum, GLenum type, GLuint, GLenum severity, GLsizei, const GLchar* message, const void*) {
    if (std::string(message).find("will use VIDEO memory as the source") != std::string::npos) {
        // Silence verbose video memory warnings
        return;
    }

    // TODO: replace with spdlog
    std::cout << "GL CALLBACK: " << std::hex << (type == GL_DEBUG_TYPE_ERROR ? "**GL ERROR**" : "") << " type = 0x"
              << type << ", severity = 0x" << severity << ", message = " << message << std::endl;
}
#endif

namespace genesis {

class WorldController;
class Renderer {
private:
    static inline Renderer* INSTANCE;

    GLFWwindow* window;
    std::shared_ptr<Camera> camera;

    std::shared_ptr<DefaultShader> textureShader;
    std::shared_ptr<TextShader> textShader;
    std::shared_ptr<ParticleShader> particleShader;

    std::shared_ptr<WorldTexture> texturePack;
    std::shared_ptr<FontAtlas> fontAtlas;

    std::shared_ptr<PhysicsWorld> physicsController;

    std::shared_ptr<InputManager> inputManager;
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

    FT_Library fontLibrary;

    // Scene management {{{
    int activeScene = 0;
    // }}}

    void initGame();
    void initFonts();

public:
    Renderer();

    void tick();
    void render();

    void run();

    GLFWwindow* getWindow() {
        return window;
    }

    double getDelta() {
        return delta;
    }

    auto getTextureShader() {
        return textureShader;
    }

    auto getTexturePack() {
        return texturePack;
    }

    auto getInputManager() {
        return inputManager;
    }

    auto getCamera() {
        return camera;
    }

    auto getFontAtlas() {
        return fontAtlas;
    }

    FT_Library& getFontLibrary() {
        return fontLibrary;
    }

    static Renderer& getInstance() {
        return *INSTANCE;
    }

    auto getActiveScene() {
        return activeScene;
    }

    auto getPhysicsEngine() {
        return this->physicsController;
    }

    auto getTextShader() {
        return textShader;
    }

    template <typename T>
    std::shared_ptr<T> getSceneByType() {
        for (auto& scene : this->activeSceneStack) {
            auto ptr = std::dynamic_pointer_cast<T>(scene);
            if (ptr) return ptr;
        }
        return nullptr;
    }

    void transition(const std::shared_ptr<Scene>& scene);
    void add(const std::shared_ptr<Scene>& scene);
    void pop(const std::shared_ptr<Scene>& scene);
};

} // namespace genesis
