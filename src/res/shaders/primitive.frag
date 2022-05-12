#version 400 core

in vec4 colorOut;

out vec4 color;

uniform sampler2D textureSampler;

void main() {
    color = colorOut;
}
