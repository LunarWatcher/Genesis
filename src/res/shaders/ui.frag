#version 460 core

in vec2 textureCoords;

out vec4 color;

uniform sampler2D textureSampler;

void main() {
    // color = vec4(1.0 - vec3(texture(textureSampler, textureCoords)), 1.0);
    color = texture(textureSampler, textureCoords);
}
