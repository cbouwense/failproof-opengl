#version 330 core
layout(location = 0) out vec4 out_color;

in vec3 v_position;
in vec3 v_color;

void main() {
    out_color = vec4((v_position + 1) / 2, 1);
}