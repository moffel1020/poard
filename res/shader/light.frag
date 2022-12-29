#version 330 core

out vec4 FragColor;

struct Material {
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 uCamPos;

in vec3 normal;
in vec3 fragPos;

void main()
{
    // calculate attenuation
    float a = 0.05;
    float b = 0.003;
    float c = 1.0;
    vec3 lightVec = light.position - fragPos;
    float dist = length(lightVec);
    float attenuation = 1.0 / (a * dist * dist + b * dist + c);

    //ambient
    vec3 ambient = light.ambient * material.diffuse;

    // diffuse
    vec3 lightDir = normalize(lightVec);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    // specular
    vec3 viewDir = normalize(uCamPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    vec3 final = (ambient + diffuse + specular) * attenuation;
    FragColor = vec4(final, 1.0);
}