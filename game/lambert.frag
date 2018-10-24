#version 150 core
uniform vec4 vLightDiffuse;
uniform vec4 vModelDiffuse;

in vec3 vsNormal;
in vec3 vsView;
in vec3 vsLight;

out vec4 fragment;

void main()
{
    vec3 diffuse = (vLightDiffuse.xyz * vModelDiffuse.xyz) * max(dot(vsLight, vsNormal), 0.0f);
    fragment = vec4(diffuse, vModelDiffuse.w);
}
