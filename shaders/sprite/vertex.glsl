#version 330 core
layout (location = 0) in vec4 vert_data;
out vec2 texture_coordinates;

uniform mat4 projection;
uniform mat4 transform = mat4(1);

void main()
{
    gl_Position = projection * transform * vec4(vert_data.xy, 0, 1);
    texture_coordinates = vert_data.zw;
}