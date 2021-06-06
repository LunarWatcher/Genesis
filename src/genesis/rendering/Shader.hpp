#pragma once

#include "GL/glew.h"
#include <string>

namespace genesis {

class Shader {
protected:
    GLuint programID;
    GLint getUniformLocation(const std::string& uniformName);

public:
    Shader(const std::string& shaderName);
    Shader(const std::string& vert, const std::string& frag);

    virtual ~Shader() = default;

    std::string loadShader(const std::string& fileName);
    void compileShader(int shaderID, const std::string& shaderSource);
    void createProgram(int vertexID, int fragmentID);

    virtual void apply() {
        glUseProgram(programID);
    }

    virtual void stop() {
        glUseProgram(0);
    }
};

} // namespace genesis
