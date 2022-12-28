#version 330 core

out vec4 FragColor;

uniform vec3 uLightColor;
uniform vec3 uLightPos;
uniform vec3 uCamPos;
uniform sampler2D uTexture;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

void main()
{
    // ambient
    float ambient = 0.1;

    // diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(uLightPos - fragPos);
    float diffuse = max(dot(norm, lightDir), 0.0);

    // specular
    float specularLight = 0.5;
    vec3 viewDir = normalize(uCamPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float specAmount = pow(max(dot(viewDir, reflectDir), 0.0), 16);
    float specular = specAmount * specularLight;

    vec3 final = (diffuse + ambient + specular) * uLightColor * vec3(texture(uTexture, texCoord));
    FragColor = vec4(final, 1.0);
}