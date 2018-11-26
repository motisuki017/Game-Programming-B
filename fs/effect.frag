#version 150 core

out vec4 fragment;
uniform float time;
uniform vec2 mousePos;

void main()
{
    fragment = vec4(sin(time), 0.0f, 0.0f, 1.0f);
}
