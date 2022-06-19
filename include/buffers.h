#pragma once
#include "core.h"

class Vbo
{
public:
    unsigned int id;
    Vbo(GLfloat* vertices, GLsizeiptr size);
    ~Vbo();

    void Bind();
    void Unbind();
};


class Ebo
{
public:
    unsigned int id;
    Ebo(GLuint* indices, GLsizeiptr size);
    ~Ebo();

    void Bind();
    void Unbind();
};


class Vao
{
public:
    unsigned int id;
    Vao();
    ~Vao();

    void AddBuffer(Vbo& vbo, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, void* offset);
    void Bind();
    void Unbind();
};