#pragma once

#include "GL/glew.h"
#include <string>
#include <vector>
#include <stdexcept>

#include "glm/glm.hpp"

namespace genesis {

class Shader {
protected:
    static inline Shader* active = nullptr;

    GLuint programID;
    GLint getUniformLocation(const std::string& uniformName);

public:
    Shader(const std::string& shaderName);
    Shader(const std::string& vert, const std::string& frag);
    Shader(const std::vector<std::pair<std::string, GLenum>>& shaders);

    virtual ~Shader() = default;

    std::string loadShader(const std::string& fileName);
    void compileShader(int shaderID, const std::string& shaderSource);
    void createProgram(const std::vector<int>& shaderIDs);

    // Why isn't this pure virtual?
    virtual void loadTransMatrix(const glm::mat4&) {
        throw std::runtime_error("loadTransMatrix called but not implemented.");
    }

    virtual void apply() {
        active = this;
        glUseProgram(programID);
    }

    virtual void stop() {
        active = nullptr;
        glUseProgram(0);
    }

    static Shader* getActive() {
        return active;
    }
};

} // namespace genesis
