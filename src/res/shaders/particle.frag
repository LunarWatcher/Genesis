#version 400 core

in vec4 inColor;

out vec4 color;

void main() {
    vec2 pos = 2 * gl_PointCoord - 1.0;
    if (dot(pos, pos) > 1.0) discard;
    color = inColor;
}
