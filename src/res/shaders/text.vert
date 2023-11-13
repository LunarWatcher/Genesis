#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 inTextureCoords;

out vec2 textureCoords;
uniform mat4 orthoMatrix;

void main() {
    gl_Position = orthoMatrix * vec4(position.xyz, 1.0);

    textureCoords = inTextureCoords;
}
