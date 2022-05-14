#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec4 colorOut;

uniform mat4 transMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    colorOut = color;

    gl_Position = projectionMatrix * viewMatrix * transMatrix * vec4(position, 1.0);
}
