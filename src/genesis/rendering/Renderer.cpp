#include "Renderer.hpp"

#include "GLFW/glfw3.h"

#include "Shader.hpp"
#include "genesis/core/WorldController.hpp"
#include "genesis/rendering/Texture.hpp"
#include "genesis/rendering/atlases/FontAtlas.hpp"
#include "shaders/DefaultShader.hpp"

#include <chrono>
#include <codecvt>
#include <iostream>
#include <locale>
#include <thread>

namespace genesis {

Renderer::Renderer() {
    INSTANCE = this;

    glewExperimental = true;
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE, false);
#if defined __APPLE__ || defined __OSX__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSwapInterval(1);

    this->window = glfwCreateWindow(1024, 576, "Genesis", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to open GLFW window");
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize glew");
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    initGame();
    initFonts();
}

void Renderer::initGame() {
    this->inputManager = std::make_shared<InputManager>();
    this->camera = std::make_shared<Camera>();

    this->texturePack = std::make_shared<genesis::WorldTexture>("images/programmer.png");

    this->worldController = std::make_shared<WorldController>();
    this->worldController->generate();

    this->textureShader = std::make_shared<DefaultShader>();
    this->textShader = std::make_shared<TextShader>();

    // Input
    glfwSetWindowUserPointer(window, inputManager.get());
    glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scanCode, int action, int mods) {
        ((InputManager*) glfwGetWindowUserPointer(win))->onKeyPressed(key, scanCode, action, mods);
    });
    glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int mods) {
        ((InputManager*) glfwGetWindowUserPointer(win))->onMousePressed(button, action, mods);
    });
    glfwSetCursorPosCallback(window, [](GLFWwindow* win, double x, double y) {
        ((InputManager*) glfwGetWindowUserPointer(win))->onMouseMoved(x, y);
    });
}

void Renderer::initFonts() {
    if (FT_Init_FreeType(&this->fontLibrary)) {
        std::cerr << "Failed to initialize freetype" << std::endl;
        throw std::runtime_error("Freetype died");
    }
    this->fontAtlas = std::make_shared<FontAtlas>();

    glGenVertexArrays(1, &textController.vao);
    glBindVertexArray(textController.vao);

    glGenBuffers(1, &textController.vertices);
    glGenBuffers(1, &textController.textureCoords);

    glBindBuffer(GL_ARRAY_BUFFER, textController.vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, textController.textureCoords);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::tick() {
    worldController->tick();
}

void Renderer::render() {

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.529, 0.8078, 0.922, 1);

    textureShader->apply();
    texturePack->bind();
    camera->applyCamera(*textureShader);

    worldController->render();

    texturePack->unbind();
    textureShader->stop();

    textShader->apply();
    fontAtlas->bind();
    renderText("LET'S GOOOOOOOOOOOOO!", 0, 0, 1.0);

    fontAtlas->unbind();
    textShader->stop();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Renderer::renderText(const std::string& text, float x, float y, float scale, const glm::vec4& color) {
    textShader->loadTextColor(color);

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(text);

    glBindVertexArray(textController.vao);

    this->fontAtlas->bind();
    for (auto& character : wide) {
        auto characterData = this->fontAtlas->getCharacter(character);
        if (!characterData) {
            continue;
        }

        float xPos = x + characterData->bitmapLeft * scale;
        float yPos = y - (characterData->bitmapHeight - characterData->bitmapTop) * scale;

        float width = characterData->bitmapWidth * scale;
        float height = characterData->bitmapHeight * scale;

        // clang-format off
        std::vector<float> points {
            xPos        , yPos + height,
            xPos        , yPos,
            xPos + width, yPos,
            xPos        , yPos + height,
            xPos + width, yPos,
            xPos + width, yPos + height
        };
        // clang-format on
        x += (characterData->advanceX >> 6) * scale;

        glBindBuffer(GL_ARRAY_BUFFER, textController.vertices);
        glBufferSubData(GL_ARRAY_BUFFER, 0, points.size() * sizeof(float), &points[0]);

        glBindBuffer(GL_ARRAY_BUFFER, textController.textureCoords);
        auto uvCoords = fontAtlas->generateUVCoords(*characterData);
        glBufferSubData(GL_ARRAY_BUFFER, 0, uvCoords.size() * sizeof(float), &uvCoords[0]);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
    }
    glBindVertexArray(0);

    this->fontAtlas->unbind();
}

void Renderer::run() {
    auto targetTime = std::chrono::duration<double, std::milli>(8.3);

    auto lastTime = std::chrono::high_resolution_clock::now();
    do {
        auto now = std::chrono::high_resolution_clock::now();
        delta = std::chrono::duration<double, std::ratio<1>>(now - lastTime).count();

        // TODO: figure out how to best design a loop that makes TPS \
        // and FPS separate (... at least partially)
        // At least to the point where FPS != TPS by loop definition
        // Though might never be a problem. A certain degree of async
        // processing might avoid that being necessesary.
        inputManager->tick();

        tick();
        render();

        auto end = std::chrono::high_resolution_clock::now();
        lastTime = end;
        auto sleepFor = targetTime - (now - end);
        if (sleepFor > std::chrono::milliseconds(0))
            std::this_thread::sleep_for(sleepFor);
    } while (glfwWindowShouldClose(window) == 0);

    glfwTerminate();
}

} // namespace genesis
