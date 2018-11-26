#version 150 core

uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProjection;
uniform vec3 vLocalLight;
uniform vec3 vLocalCamera;

in vec3 position;

void main()
{
    gl_Position = mProjection * mView * vec4(position, 1.0f);
}
