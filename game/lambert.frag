#version 150 core
uniform vec4 vLightDiffuse;
uniform vec4 vModelDiffuse;

out vec4 fragment;

in vec3 vsNormal;
in vec3 vsView;
in vec3 vsLight;

uniform float time;
uniform vec2 mousePos;
uniform vec2 windowSize;

void main()
{
    vec3 diffuse = (vLightDiffuse.xyz * vModelDiffuse.xyz) * max(dot(vsLight, vsNormal), 0.0f);
    fragment = vec4(diffuse, vModelDiffuse.w);
}
