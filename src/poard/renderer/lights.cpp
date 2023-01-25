#include "lights.h"


DirLight::DirLight(glm::vec3 direction, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 ambient)
    : direction(direction), Light(diffuse, specular, ambient) { }

void DirLight::upload(Shader& shader) {
    shader.bind();
    shader.uploadVec3("dirLight.direction", direction);
    shader.uploadVec3("dirLight.diffuse", diffuse);
    shader.uploadVec3("dirLight.specular", specular);
    shader.uploadVec3("dirLight.ambient", ambient);
}


PointLight::PointLight(glm::vec3 position, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 ambient)
    : position(position), Light(diffuse, specular, ambient) { }

void PointLight::upload(Shader& shader, uint32_t index) {
    shader.bind();
    std::string num = std::to_string(index);
    shader.uploadVec3(("pointLights[" + num + "].position").c_str(), position);
    shader.uploadVec3(("pointLights[" + num + "].diffuse").c_str(), diffuse);
    shader.uploadVec3(("pointLights[" + num + "].specular").c_str(), specular);
    shader.uploadVec3(("pointLights[" + num + "].ambient").c_str(), ambient);
    shader.uploadFloat(("pointLights[" + num + "].quadratic").c_str(), quadratic);
    shader.uploadFloat(("pointLights[" + num + "].linear").c_str(), linear);
    shader.uploadFloat(("pointLights[" + num + "].constant").c_str(), constant);
}


SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, float outerCone, float innerCone)
    : position(position), 
        direction(direction), 
        outer(glm::cos(glm::radians(outerCone))),  // shader needs cosine value directly
        inner(glm::cos(glm::radians(innerCone))),
        Light(glm::vec3(1.0f), glm::vec3(0.5f), glm::vec3(0.0f)) { }

void SpotLight::upload(Shader& shader, uint32_t index) {
    shader.bind();
    std::string num = std::to_string(index);
    shader.uploadVec3(("spotLights[" + num + "].position").c_str(), position);
    shader.uploadVec3(("spotLights[" + num + "].direction").c_str(), direction);
    shader.uploadVec3(("spotLights[" + num + "].diffuse").c_str(), diffuse);
    shader.uploadVec3(("spotLights[" + num + "].specular").c_str(), specular);
    shader.uploadVec3(("spotLights[" + num + "].ambient").c_str(), ambient);
    shader.uploadFloat(("spotLights[" + num + "].constant").c_str(), constant);
    shader.uploadFloat(("spotLights[" + num + "].quadratic").c_str(), quadratic);
    shader.uploadFloat(("spotLights[" + num + "].linear").c_str(), linear);
    shader.uploadFloat(("spotLights[" + num + "].inner").c_str(), inner);
    shader.uploadFloat(("spotLights[" + num + "].outer").c_str(), outer);
}