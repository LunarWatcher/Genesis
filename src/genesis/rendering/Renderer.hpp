#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Model.hpp"
#include "Renderable.hpp"

#include "genesis/rendering/atlases/FontAtlas.hpp"
#include "genesis/rendering/atlases/WorldTexture.hpp"
#include "genesis/rendering/particles/ParticleEmitter.hpp"
#include "genesis/rendering/shaders/ParticleShader.hpp"
#include "genesis/rendering/shaders/TextShader.hpp"
#include "genesis/rendering/ui/Text.hpp"
#include "genesis/rendering/view/Camera.hpp"

#include "genesis/math/physics/PhysicsWorld.hpp"

#include <iostream>
#include <memory>
#include <vector>

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

    std::shared_ptr<WorldController> worldController;
    std::shared_ptr<PhysicsWorld> physicsController;

    std::shared_ptr<InputManager> inputManager;

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

    auto getWorld() {
        return worldController;
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
};

} // namespace genesis
