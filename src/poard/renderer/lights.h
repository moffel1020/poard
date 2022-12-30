#pragma once
#include "shader.h"


class Light
{
public:
    void setDiffuse(const glm::vec3& diff) { diffuse = diff; }
    void setAmbient(const glm::vec3& amb) { ambient = amb; }
    void setSpecular(const glm::vec3& spec) { specular = spec; }

public:
    glm::vec3 diffuse;
    glm::vec3 ambient;
    glm::vec3 specular;
};



class DirLight : public Light
{
public:
    DirLight(glm::vec3 direction, glm::vec3 diffuse=glm::vec3(0.4f), glm::vec3 ambient=glm::vec3(0.2f), glm::vec3 specular=glm::vec3(0.5f));
    void upload(Shader& shader);

private:
    glm::vec3 direction;
    using Light::diffuse;
    using Light::ambient;
    using Light::specular;
};



class PointLight : public Light
{
public:
    PointLight(glm::vec3 position, glm::vec3 diffuse=glm::vec3(1.0f), glm::vec3 ambient=glm::vec3(0.1f), glm::vec3 specular=glm::vec3(0.5f)); 
    void upload(Shader& shader, uint32_t index);
    glm::vec3 getPosition() { return position; }

private:
    glm::vec3 position;
    float quadratic = 0.20f;
    float linear = 0.25f;
    float constant = 1.0f;
    using Light::diffuse;
    using Light::ambient;
    using Light::specular;
};



class SpotLight : public Light
{
public:
    SpotLight(glm::vec3 position, glm::vec3 direction, float outerCone, float innerCone);
    void upload(Shader& shader, uint32_t index);
    glm::vec3 getPosition() { return position; }
    void setPosition(const glm::vec3& pos) { position = pos; }

private:
    glm::vec3 position;
    glm::vec3 direction;
    float inner;
    float outer;
    float quadratic = 0.05f;
    float linear = 0.003f;
    float constant = 1.0f;
    using Light::diffuse;
    using Light::ambient;
    using Light::specular;
};