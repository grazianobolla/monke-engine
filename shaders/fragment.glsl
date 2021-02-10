#version 330 core
out vec4 color;
in vec2 texture_coordinates;

uniform sampler2D text;

void main()
{
    color = texture(text, texture_coordinates);
} 