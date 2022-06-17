#pragma once
#include "core.h"

class Vbo
{
public:
    unsigned int id;
    Vbo(GLfloat* vertices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};


class Ebo
{
public:
    unsigned int id;
    Ebo(GLuint* indices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};


class Vao
{
public:
    unsigned int id;
    Vao();
    void LinkAttrib(Vbo vbo, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, void* offset);

    void Bind();
    void Unbind();
    void Delete();
};