#pragma once
#include "core.h"

class VertexBuffer
{
public:
    VertexBuffer(GLfloat* vertices, GLsizeiptr size);
    ~VertexBuffer();
    void bind();
    void unbind();
private:
    uint32_t id;
};


class IndexBuffer
{
public:
    IndexBuffer(GLuint* indices, uint32_t count);
    uint32_t getCount() { return count; }
    ~IndexBuffer();
    void bind();
    void unbind();
private:
    uint32_t id;
    uint32_t count;
};


class VertexArray
{
public:
    VertexArray();
    ~VertexArray();
    void addBuffer(VertexBuffer& vbo, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, void* offset);
    void bind();
    void unbind();
private:
    uint32_t id;
};