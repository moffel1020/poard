#version 330 core

out vec4 FragColor;

uniform vec3 uLightColor;
uniform vec3 uLightPos;

in vec3 normal;
in vec3 fragPos;
in vec3 color;

void main()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(uLightPos - fragPos);

    float angle = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = angle * uLightColor;

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * uLightColor;

    vec3 final = (ambient + diffuse) * color;
    FragColor = vec4(final, 1.0);
}