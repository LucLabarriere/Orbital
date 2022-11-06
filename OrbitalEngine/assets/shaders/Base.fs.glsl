#version 420 core

in vec4 v_Color;
in vec4 v_Position;

uniform vec4 u_Color;

out vec4 o_Color;

void main()
{
	float distance = length(gl_FragCoord);
    o_Color = u_Color;
}
