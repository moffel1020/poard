#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

struct Material {
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float quadratic;
    float linear;
    float constant;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float inner;
    float outer;

    float quadratic;
    float linear;
    float constant;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight;

#define MAX_POINT_LIGHTS 10 
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform float uPointLightCount;

#define MAX_SPOT_LIGHTS 10
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform float uSpotLightCount;

uniform Material material;
uniform float uUseTexture;
uniform sampler2D diffuse_texture0;
uniform sampler2D specular_texture0;

uniform vec3 uCamPos;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 matDiff, vec3 matSpec);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos, vec3 matDiff, vec3 matSpec);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 fragPos, vec3 matDiff, vec3 matSpec);

void main() {
    vec3 viewDir = normalize(uCamPos - fragPos);

    vec3 matDiffuse = vec3(1.0);
    vec3 matSpecular = vec3(1.0);

    if (uUseTexture == 1.0) {
        matDiffuse = texture(diffuse_texture0, texCoord).rgb;
        matSpecular = texture(specular_texture0, texCoord).rgb;
    } else {
        matDiffuse = material.diffuse;
        matSpecular = material.specular;
    }

    vec3 result = calcDirLight(dirLight, normal, viewDir, matDiffuse, matSpecular);

    for (int i = 0; i < uPointLightCount; i++) {
        result += calcPointLight(pointLights[i], normal, viewDir, fragPos, matDiffuse, matSpecular);
    }

    for (int i = 0; i < uSpotLightCount; i++) {
        result += calcSpotLight(spotLights[i], normal, viewDir, fragPos, matDiffuse, matSpecular);
    }

    FragColor = vec4(result, 1.0);
}


vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 matDiff, vec3 matSpec) {
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * matDiff;
    vec3 diffuse = light.diffuse * diff * matDiff;
    vec3 specular = light.specular * spec * matSpec;

    return ambient + diffuse + specular;
}


vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos, vec3 matDiff, vec3 matSpec) {
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

    vec3 ambient = light.ambient * matDiff;
    vec3 diffuse = light.diffuse * diff * matDiff;
    vec3 specular = light.specular * spec * matSpec;
    return attenuation * (ambient + diffuse + specular);
}


vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 fragPos, vec3 matDiff, vec3 matSpec) {
    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));

    if (theta > light.outer) {
        float epsilon = light.inner - light.outer;
        float intensity = clamp((theta - light.outer) / epsilon, 0.0, 1.0);

        float diff = max(dot(normal, lightDir), 0.0);

        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);


        vec3 ambient = light.ambient * matDiff;
        vec3 diffuse = light.diffuse * diff * matDiff;
        vec3 specular = light.specular * spec * matSpec;

        return attenuation * (ambient + (intensity * (diffuse + specular)));
    } else {
        return attenuation * (light.ambient * matDiff.rgb);
    }
}