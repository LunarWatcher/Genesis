#version 400 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 inTextureCoords;

out vec2 textureCoords;

void main() {
    gl_Position = vec4(position.x, position.y, 0.0, 0.0);

    textureCoords = inTextureCoords;
}
