#version 420 core

in vec4 v_Color;
in vec4 v_Position;

uniform vec4 u_Color;

out vec4 o_Color;

void main()
{
	float distance = 0.5 - length(v_Position.xy);
	//distance = step(0.0, distance);
	float fade = 0.01;
	distance = smoothstep(0.0, fade, distance);
	o_Color = u_Color;
	o_Color.w = distance;
}
