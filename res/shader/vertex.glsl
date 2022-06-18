#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTextCoord;

uniform mat4 transform;

out vec3 color;
out vec2 TextCoord;

void main()
{
	gl_Position = transform * vec4(aPos, 1.0);
	color = aColor;
	TextCoord = aTextCoord;
}