#pragma once
#include "shader.h"
#include "buffers.h"

class Renderer
{
public:
    void draw(VertexArray& va, IndexBuffer& ib, Shader& shader);
    void clear();
};