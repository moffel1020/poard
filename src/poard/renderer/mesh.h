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
private:
    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ibo;
};