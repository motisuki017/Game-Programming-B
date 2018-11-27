#version 150 core

out vec4 fragment;
uniform float time;
uniform vec2 mousePos;
uniform vec2 windowSize;
uniform sampler2D image;

void main()
{
	float phase = 1.0e-2 * length(gl_FragCoord.xy - mousePos.xy);
	float color = sin(time * 3.0 + phase);
    fragment = vec4(color, 0.0f, 0.0f, 1.0f);
}
