#version 400 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 inTextureCoords;

out vec2 textureCoords;

uniform mat4 orthoMatrix;
uniform mat4 transMatrix;

void main() {
    gl_Position = orthoMatrix * vec4(position.xy, 0.0, 1.0);

    textureCoords = inTextureCoords;
}
