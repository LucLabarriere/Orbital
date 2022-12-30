#version 420 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Color;

uniform mat4 u_Model = mat4(1.0f);
uniform mat4 u_View = mat4(1.0f);

out vec4 v_Color;
out vec4 v_Position;

void main()
{
    v_Position = vec4(a_Position, 1.0);
    gl_Position = u_View * u_Model * v_Position;
    v_Color = vec4(a_Color, 1.0);
}
