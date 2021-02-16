#version 330 core
out vec4 color;
in vec2 texture_coordinates;

uniform sampler2D tex;
uniform vec4 tint = vec4(1);

void main()
{
    color = texture(tex, texture_coordinates) * tint;
} 