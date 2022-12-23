#include "core.h"
#include "renderer.h"


void Renderer::draw(VertexArray& va, IndexBuffer& ib, Shader& shader) {
    va.bind();
    ib.bind();
    shader.bind();
    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}