#version 330 core
layout(location = 0) in vec3 a_position;

void main() {
    gl_Position = a_position;
}