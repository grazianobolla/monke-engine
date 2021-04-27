#version 330 core
layout (location = 0) in vec2 vert_data;
layout (location = 1) in vec2 uv_data;
out vec2 texture_coordinates;

uniform mat4 model;
uniform mat4 projection;
//uniform mat4 view;

void main()
{
    gl_Position = projection * model * vec4(vert_data, 0, 1);
    texture_coordinates = uv_data;
}