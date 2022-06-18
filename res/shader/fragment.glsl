#version 460 core

out vec4 FragColor;
in vec3 color;
in vec2 TextCoord;

uniform sampler2D uTexture;

void main()
{
	FragColor = texture(uTexture, TextCoord);
}