#version 330 core

out vec4 FragColor;
in vec3 passedColor;

void main() {
  FragColor = vec4(passedColor, 1.0);
}
