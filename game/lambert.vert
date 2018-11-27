#version 150 core

uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProjection;
uniform vec3 vLocalLight;
uniform vec3 vLocalCamera;
uniform float time;
uniform vec2 mousePos;
uniform vec2 windowSize;

in vec3 position;
in vec3 normal;

out vec3 vsNormal;
out vec3 vsView;
out vec3 vsLight;

void main()
{
    gl_Position = mProjection * mView * mModel * vec4(position, 1.0f);
    vsNormal    = normal;
    vsView      = normalize(vLocalCamera - position.xyz);
    vsLight     = normalize(vLocalLight - position.xyz);
}
