#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 inTextureCoords;

out vec2 textureCoords;

uniform mat4 transMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    gl_Position = projectionMatrix * viewMatrix * transMatrix * vec4(position, 1.0);

    textureCoords = inTextureCoords;
}
