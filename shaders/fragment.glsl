#version 330 core
out vec4 fragment;
in vec2 texture_coordinates;

uniform sampler2D tex;

void main()
{
    vec4 f = texture(tex, texture_coordinates);
    if(f.a == 0) discard;
    fragment = f;
} 