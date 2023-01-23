#include "mesh.h"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures) 
    : vertices(vertices), indices(indices), textures(textures) {
    
    this->vao = VertexArray();
    this->vbo = VertexBuffer(vertices);
    this->ibo = IndexBuffer(indices);

    vao.addBuffer(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
    vao.addBuffer(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    vao.addBuffer(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
}

void Mesh::draw(Shader& shader) {
    for(uint32_t i = 0; i < textures.size(); i++) {
        TextureType texType = textures[i].getType();

        switch (texType) {
            // see phong.frag file
            case DIFFUSE:
                textures[i].bind(GL_TEXTURE0);
                break;
            case SPECULAR:
                textures[i].bind(GL_TEXTURE1);
                break;
            default:
                std::cout << "texture is not a diffuse or specular texture" << std::endl;
                break;
        }

        Renderer::draw(vao, ibo, shader);
    }
}