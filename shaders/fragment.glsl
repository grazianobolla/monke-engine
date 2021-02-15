#version 330 core
out vec4 color;
in vec2 texture_coordinates;

uniform sampler2D tex;

void main()
{
    color = texture(tex, texture_coordinates);
} 