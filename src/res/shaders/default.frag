#version 400 core

//in vec2 UV;

out vec4 color;

//uniform sampler2D textureSampler;

void main() {
    //color.xyz = texture(textureSampler, UV).rgb;
    //color.w = 1.0; // Alpha
    color = vec4(1, 0, 0, 1);
}
