#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 inTextureCoords;

out vec2 textureCoords;

void main() {
    gl_Position = projectionMatrix * viewMatrix * transMatrix * vec4(position, 1.0);

    textureCoords = inTextureCoords;
}
