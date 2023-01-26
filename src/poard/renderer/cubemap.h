#pragma once
#include "core.h"
#include "buffers.h"
#include "shader.h"
#include "stb/stb_image.h"
#include "renderer.h"
#include "application.h"
#include "camera.h"


class Cubemap
{
public:
    Cubemap(const std::string& directory);
    void draw(Shader& cubemapShader);
    void bind(uint32_t slot = GL_TEXTURE0);
private:
    uint32_t id;
    int width;
    int height;
    int comp;

    std::unique_ptr<VertexArray> vao;
    std::unique_ptr<VertexBuffer> vbo;
    std::unique_ptr<IndexBuffer> ibo;

    float vertices[24] = {
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f
    };

    uint32_t indices[36] = {
        1, 2, 6,
        6, 5, 1,
        0, 4, 7,
        7, 3, 0,
        4, 5, 6,
        6, 7, 4,
        0, 3, 2,
        2, 1, 0,
        0, 1, 5,
        5, 4, 0,
        3, 7, 6,
        6, 2, 3
    };
};