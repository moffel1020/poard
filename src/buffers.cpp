#include "core.h"
#include "buffers.h"

// vbo
Vbo::Vbo(GLfloat* vertices, GLsizeiptr size)
{
    glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void Vbo::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void Vbo::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Vbo::Delete()
{
    glDeleteBuffers(1, &id);
}



// ebo
Ebo::Ebo(GLuint* indices, GLsizeiptr size)
{
    glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}
void Ebo::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void Ebo::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Ebo::Delete()
{
    glDeleteBuffers(1, &id);
}



// vao
Vao::Vao()
{
    glGenVertexArrays(1, &id);
}

void Vao::LinkAttrib(Vbo vbo, GLuint location, GLuint size, GLenum type, GLsizeiptr stride, void* offset)
{
    vbo.Bind();
    glVertexAttribPointer(location, size, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(location);
    vbo.Unbind();
}

void Vao::Bind()
{
    glBindVertexArray(id);
}

void Vao::Unbind()
{
    glBindVertexArray(0);
}

void Vao::Delete()
{
    glDeleteVertexArrays(1, &id);
}