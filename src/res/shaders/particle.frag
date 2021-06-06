#version 400 core

// I imagine we can use this for something.
in float age;

// TODO: make the color a uniform
// Or maybe make it easier for different particles to have different fragment shaders?
out vec4 color;

void main() {
    color = vec4(1.0, 0.0, 1.0, 1.0);
}
