#version 400 core

in vec2 textureCoords;

out vec4 color;

uniform sampler2D textureSampler;
uniform vec4 textColor;

void main() {
    vec4 interm = textColor * vec4(1.0, 1.0, 1.0, texture(textureSampler, textureCoords).r);

    // TODO: Fix this nasty hack
    if (interm.a == 0) {
        interm = vec4(0, 0, 0, 0.0001);
    }

    color = interm;
}
