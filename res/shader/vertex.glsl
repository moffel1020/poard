#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 transform;

out vec3 color;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0);
	color = aColor;
}