#version 460 core

in vec2 textureCoords;

out vec4 color;

uniform sampler2D textureSampler;
uniform vec4 textColor;
uniform vec4 backgroundColour;


void main() {
    float alphaChannel = textureCoords.x == -1.0 ? -1 : texture(textureSampler, textureCoords).r;

    if (alphaChannel >= 0.4) {
        color = textColor * vec4(1.0, 1.0, 1.0, alphaChannel);
    } else if (alphaChannel == -1) {
        color = backgroundColour;
    } else {
        discard;
    }
}
