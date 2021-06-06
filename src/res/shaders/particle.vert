#version 400 core

// The raw vertex quad positions
layout (location = 0) in vec3 vertPos;
// The actual position of the particle
// The fourth value contains the age
layout (location = 1) in vec4 position;
// The particle size - stored as an attribute instead
// of a uniform to allow varying sizes
layout (location = 2) in float particleSize;

// Standard matrices
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out float age;

void main() {
    vec4 viewSpace = viewMatrix * vec4(position.xyz, 1);
    viewSpace.xy += particleSize * (vertPos.xy - vec2(0.5));

    // Output
    gl_Position = projectionMatrix * viewSpace;
    age = position.w;
}
