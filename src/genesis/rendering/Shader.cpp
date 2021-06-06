#include "Shader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace genesis {

Shader::Shader(const std::string& shaderName) : Shader(shaderName + ".vert", shaderName + ".frag") {}

Shader::Shader(const std::string& vert, const std::string& frag) {

    GLint vertexID = glCreateShader(GL_VERTEX_SHADER);
    GLint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

    auto vertexSource = loadShader(vert);
    auto fragSource = loadShader(frag);

    compileShader(vertexID, vertexSource);
    compileShader(fragmentID, fragSource);
    createProgram(vertexID, fragmentID);
}

std::string Shader::loadShader(const std::string& fileName) {
    std::string shaderSource;
    std::ifstream stream("shaders/" + fileName);
    if (stream.is_open()) {
        std::stringstream ss;
        ss << stream.rdbuf();
        return ss.str();
    }
    throw std::runtime_error("Failed to open shader file: shaders/" + fileName);
}

void Shader::compileShader(int shaderID, const std::string& shaderSource) {
    GLint result = GL_FALSE;
    int logLength;
    const char* strPointer = shaderSource.c_str();
    glShaderSource(shaderID, 1, &strPointer, nullptr);
    glCompileShader(shaderID);

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        std::vector<char> message(logLength + 1);
        glGetShaderInfoLog(shaderID, logLength, nullptr, &message[0]);
        std::cerr << "Compiling shader failed; " << std::endl;
        std::cerr << &message[0] << std::endl;

        throw new std::runtime_error("Failed to load shader");
    }
}

void Shader::createProgram(int vertexID, int fragmentID) {
    GLint result = GL_FALSE;
    int logLength;

    this->programID = glCreateProgram();
    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        std::vector<char> errorMessage(logLength + 1);
        glGetProgramInfoLog(programID, logLength, nullptr, &errorMessage[0]);
        std::cerr << &errorMessage[0] << std::endl;
        throw std::runtime_error("Failed to link program");
    }

    glDetachShader(programID, vertexID);
    glDetachShader(programID, fragmentID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}

GLint Shader::getUniformLocation(const std::string& name) {
    return glGetUniformLocation(this->programID, name.c_str());
}

} // namespace genesis
