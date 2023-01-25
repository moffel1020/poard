#pragma once
#include "shader.h"


class Light
{
public:
    Light() { };
    Light(const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& ambient) 
        : diffuse(diffuse), specular(specular), ambient(ambient) { }

    void setDiffuse(const glm::vec3& diff) { diffuse = diff; }
    void setSpecular(const glm::vec3& spec) { specular = spec; }
    void setAmbient(const glm::vec3& amb) { ambient = amb; }

protected:
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 ambient;
};



class DirLight : public Light
{
public:
    DirLight(glm::vec3 direction, glm::vec3 diffuse=glm::vec3(0.4f), glm::vec3 specular=glm::vec3(0.5f), glm::vec3 ambient=glm::vec3(0.1f));
    void upload(Shader& shader);
    void setDirection(const glm::vec3& dir) { direction = dir; }

private:
    glm::vec3 direction;
};



class PointLight : public Light
{
public:
    PointLight(glm::vec3 position, glm::vec3 diffuse=glm::vec3(1.0f), glm::vec3 specular=glm::vec3(0.5f), glm::vec3 ambient=glm::vec3(0.0f)); 
    void upload(Shader& shader, uint32_t index);
    glm::vec3 getPosition() { return position; }
    void setPosition(const glm::vec3& pos) { position = pos; }
    void setPosition(float x, float y, float z) { position = glm::vec3(x, y, z); }
    void setLinear(float l) { linear = l; }
    void setQuadratic(float q) { quadratic = q; }

private:
    glm::vec3 position;
    float quadratic = 0.05f;
    float linear = 0.003;
    float constant = 1.0f;
};



class SpotLight : public Light
{
public:
    SpotLight(glm::vec3 position, glm::vec3 direction, float outerCone, float innerCone);
    void upload(Shader& shader, uint32_t index);
    glm::vec3 getPosition() { return position; }
    void setPosition(const glm::vec3& pos) { position = pos; }
    void setPosition(float x, float y, float z) { position = glm::vec3(x, y, z); }
    void setLinear(float l) { linear = l; }
    void setQuadratic(float q) { quadratic = q; }
    void setDirection(const glm::vec3& dir) { direction = dir; }

private:
    glm::vec3 position;
    glm::vec3 direction;
    float inner;
    float outer;
    float quadratic = 0.05f;
    float linear = 0.003f;
    float constant = 1.0f;
};