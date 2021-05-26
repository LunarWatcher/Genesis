#version 400 core

in vec2 textureCoords;

out vec4 color;

uniform sampler2D textureSampler;

void main() {
    color = texture(textureSampler, textureCoords);
}
