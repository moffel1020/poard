#pragma once
#include "core.h"

class VertexBuffer
{
public:
    uint32_t id;
    VertexBuffer(GLfloat* vertices, GLsizeiptr size);
    ~VertexBuffer();

    void bind();
    void unbind();
};


class IndexBuffer
{
public:
    uint32_t id;
    IndexBuffer(GLuint* indices, GLsizeiptr size);
    ~IndexBuffer();

    void bind();
    void unbind();
};


class VertexArray
{
public:
    uint32_t id;
    VertexArray();
    ~VertexArray();

    void addBuffer(VertexBuffer& vbo, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, void* offset);
    void bind();
    void unbind();
};