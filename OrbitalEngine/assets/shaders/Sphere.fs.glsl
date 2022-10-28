#version 420 core

in vec4 v_Color;
in vec4 v_Position;

out vec4 o_Color;

void main()
{
	float distance = 0.5 - length(v_Position.xy);
	distance = step(0.0, distance);
    o_Color = vec4(distance);
}
