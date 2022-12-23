#include "core.h"
#include "buffers.h"

// vbo
VertexBuffer::VertexBuffer(GLfloat* vertices, GLsizeiptr size) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &id);
}



// ebo
IndexBuffer::IndexBuffer(GLuint* indices, uint32_t count) {
    this->count = count;
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_STATIC_DRAW);
}

void IndexBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &id);
}



// vao
VertexArray::VertexArray() {
    glGenVertexArrays(1, &id);
}

void VertexArray::addBuffer(VertexBuffer& vbo, GLuint location, GLuint size, GLenum type, GLsizeiptr stride, void* offset) {
    bind();
    vbo.bind();
    glVertexAttribPointer(location, size, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(location);
    vbo.unbind();
}

void VertexArray::bind() {
    glBindVertexArray(id);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id);
}