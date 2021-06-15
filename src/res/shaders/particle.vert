#version 400 core

// The raw vertex quad positions
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in float particleSize;

// Standard matrices
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 inColor;

void main() {
    vec4 viewSpace = viewMatrix * vec4(position.xyz, 1.0);
    gl_PointSize = particleSize;

    // Output
    gl_Position = projectionMatrix * viewSpace;
    inColor = color;
}
