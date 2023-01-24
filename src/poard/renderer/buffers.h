#pragma once
#include "core.h"


struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};


class VertexBuffer
{
public:
    VertexBuffer(GLfloat* vertices, GLsizeiptr size);
    VertexBuffer(std::vector<Vertex> vertices);
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
    IndexBuffer(std::vector<GLuint> indices);
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
    void addBuffer(VertexBuffer& vbo, GLuint layout, GLuint count, GLenum type, GLsizeiptr stride, void* offset);
    void bind();
    void unbind();
private:
    uint32_t id;
};