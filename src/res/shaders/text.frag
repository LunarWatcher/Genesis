#version 400 core

in vec2 textureCoords;

out vec4 color;

uniform sampler2D textureSampler;
uniform vec4 textColor;

void main() {
    color = textColor * vec4(1.0, 1.0, 1.0, texture(textureSampler, textureCoords).r);
}
