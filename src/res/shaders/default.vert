#version 400 core

layout(location = 0) in vec3 position;
//layout(location = 1) in vec2 inUV;

//out vec2 UV;

void main() {
  gl_Position.xyz = position;
  gl_Position.w = 1.0;

  //UV = inUV;
}
