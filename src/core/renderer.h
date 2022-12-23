#pragma once
#include "shader.h"
#include "buffers.h"

class Renderer
{
public:
    static void draw(VertexArray& va, IndexBuffer& ib, Shader& shader);
    static void clear();
};