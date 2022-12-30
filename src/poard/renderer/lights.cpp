#include "lights.h"


DirLight::DirLight(glm::vec3 direction, glm::vec3 diffuse, glm::vec3 ambient, glm::vec3 specular)
    : direction(direction) {
    this->diffuse = diffuse;
    this->ambient = ambient;
    this->specular = specular;
}

void DirLight::upload(Shader& shader) {
    shader.bind();
    shader.uploadVec3("dirLight.direction", direction);
    shader.uploadVec3("dirLight.diffuse", diffuse);
    shader.uploadVec3("dirLight.ambient", ambient);
    shader.uploadVec3("dirLight.specular", specular);
}


PointLight::PointLight(glm::vec3 position, glm::vec3 diffuse, glm::vec3 ambient, glm::vec3 specular)
    : position(position) {
    this->diffuse = diffuse;
    this->ambient = ambient;
    this->specular = specular;
}

void PointLight::upload(Shader& shader) {
    shader.bind();
    shader.uploadVec3("pointLight.position", position);
    shader.uploadVec3("pointLight.ambient", ambient);
    shader.uploadVec3("pointLight.diffuse", diffuse);
    shader.uploadVec3("pointLight.specular", specular);
    shader.uploadFloat("pointLight.quadratic", quadratic);
    shader.uploadFloat("pointLight.linear", linear);
    shader.uploadFloat("pointLight.constant", constant);
}


SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, float outerCone, float innerCone)
    : position(position), direction(direction), outer(glm::cos(glm::radians(outerCone))), inner(glm::cos(glm::radians(innerCone)))  {
    this->ambient = glm::vec3(0.2f);
    this->diffuse = glm::vec3(1.0f);
    this->specular = glm::vec3(0.5f);
}

void SpotLight::upload(Shader& shader) {
    shader.bind();
    shader.uploadVec3("spotLight.position", position);
    shader.uploadVec3("spotLight.direction", direction);
    shader.uploadVec3("spotLight.ambient", ambient);
    shader.uploadVec3("spotLight.diffuse", diffuse);
    shader.uploadVec3("spotLight.specular", specular);
    shader.uploadFloat("spotLight.constant", constant);
    shader.uploadFloat("spotLight.quadratic", quadratic);
    shader.uploadFloat("spotLight.linear", linear);
    shader.uploadFloat("spotLight.inner", inner);
    shader.uploadFloat("spotLight.outer", outer);
}