#version 330 core

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 uCamPos;
uniform Material material;
uniform Light light;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

void main()
{
    //ambient
    vec3 ambient = light.ambient * texture(material.diffuse, texCoord).rgb;

    // diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * texture(material.diffuse, texCoord).rgb);

    // specular
    vec3 viewDir = normalize (uCamPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * texture(material.specular, texCoord).rgb);

    vec3 final = ambient + diffuse + specular;
    FragColor = vec4(final, 1.0);
}