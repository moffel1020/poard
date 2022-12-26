#version 330 core

out vec4 FragColor;

uniform vec3 uObjectColor;
uniform vec3 uLightColor;

void main()
{
    float ambientLight = 0.1;
    FragColor = vec4(uObjectColor * ambientLight * uLightColor, 1.0);
}