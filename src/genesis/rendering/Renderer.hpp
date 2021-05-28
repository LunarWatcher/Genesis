#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Model.hpp"
#include "Renderable.hpp"
#include "genesis/rendering/atlases/FontAtlas.hpp"
#include "genesis/rendering/atlases/WorldTexture.hpp"
#include "genesis/rendering/shaders/TextShader.hpp"
#include "genesis/rendering/view/Camera.hpp"
#include <memory>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace genesis {

class WorldController;
class Renderer {
private:
    static inline Renderer* INSTANCE;

    GLFWwindow* window;
    std::shared_ptr<Camera> camera;

    std::shared_ptr<DefaultShader> textureShader;
    std::shared_ptr<TextShader> textShader;

    std::shared_ptr<WorldTexture> texturePack;
    std::shared_ptr<FontAtlas> fontAtlas;

    std::shared_ptr<WorldController> worldController;
    std::shared_ptr<InputManager> inputManager;
    double delta;

    FT_Library fontLibrary;
    struct TextController {
        GLuint vao, vertices, textureCoords;
    } textController;

    void initGame();
    void initFonts();

public:
    Renderer();

    void tick();
    void render();

    void renderText(
        const std::string& text, float x, float y, float scale, const glm::vec4& color = {1.0, 0.0, 0.0, 1.0});

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

    FT_Library& getFontLibrary() {
        return fontLibrary;
    }

    static Renderer getInstance() {
        return *INSTANCE;
    }
};

} // namespace genesis
