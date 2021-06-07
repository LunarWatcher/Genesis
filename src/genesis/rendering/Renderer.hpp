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

#include <iostream>
#include <memory>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

#ifdef API_DEBUG
inline void GLAPIENTRY MessageCallback(
    GLenum, GLenum type, GLuint, GLenum severity, GLsizei, const GLchar* message, const void*) {
    std::cout << "GL CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") << " type = " << type
              << ", severity = " << severity << ", message = " << message << std::endl;
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
    std::shared_ptr<InputManager> inputManager;

    std::shared_ptr<TextModel> text;
    double delta;

    FT_Library fontLibrary;
    // Text testing
    std::shared_ptr<Model> textModel;

    // Particle testing
    std::shared_ptr<Model> particleEmitter;

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

    static Renderer getInstance() {
        return *INSTANCE;
    }
};

} // namespace genesis
