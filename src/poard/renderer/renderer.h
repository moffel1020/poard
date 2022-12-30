#pragma once
#include "core.h"
#include "shader.h"
#include "buffers.h"

class Renderer
{
public:
    static void draw(VertexArray& va, IndexBuffer& ib, Shader& shader);
    static void drawTriangles(VertexArray& va, Shader& shader, GLsizei count);
    static void clear();
};