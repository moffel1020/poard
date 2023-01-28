#pragma once
#include "core.h"
#include "texture.h"
#include "shader.h"
#include "buffers.h"
#include "renderer.h"


class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
    void draw(Shader& shader);

    void setDiffuse(const glm::vec3& diff) { diffuse = diff; }
    void setSpecular(const glm::vec3& spec) { specular = spec; }
    void setShininess(float s) { shininess = s; }
private:
    std::unique_ptr<VertexArray> vao;
    std::unique_ptr<VertexBuffer> vbo;
    std::unique_ptr<IndexBuffer> ibo;

    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};