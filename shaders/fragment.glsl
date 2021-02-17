#version 330 core
out vec4 fragment;
in vec2 texture_coordinates;

uniform sampler2D tex;
uniform vec4 tint = vec4(1);

void main()
{
    vec4 f = texture(tex, texture_coordinates) * tint;
    if(f.a == 0) discard;
    fragment = f;
} 