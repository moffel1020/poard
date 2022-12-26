#version 330 core

out vec4 FragColor;

uniform vec3 uLightColor;
uniform vec3 uLightPos;
uniform vec3 uCamPos;

in vec3 normal;
in vec3 fragPos;
in vec3 color;

void main()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(uLightPos - fragPos);

    float angle = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = angle * uLightColor;

    float specularLight = 0.5;
    vec3 viewDir = normalize(uCamPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float specAmount = pow(max(dot(viewDir, reflectDir), 0.0), 16);
    float specular = specAmount * specularLight;

    float ambientStrength = 0.1;
    vec3 final = (diffuse + ambientStrength + specular) * color;
    FragColor = vec4(final, 1.0);
}