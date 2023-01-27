#include "mesh.h"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures) 
    : vertices(vertices), indices(indices), textures(textures) {
    
    this->vao = std::make_unique<VertexArray>();
    this->vbo = std::make_unique<VertexBuffer>(vertices);
    this->ibo = std::make_unique<IndexBuffer>(indices);

    vao->addBuffer(*vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
    vao->addBuffer(*vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    vao->addBuffer(*vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
}


void Mesh::draw(Shader& shader, const glm::mat4& model, const glm::mat3& inverseModel) {
    shader.uploadVec3("material.diffuse", diffuse);
    shader.uploadVec3("material.specular", specular);
    shader.uploadFloat("material.shininess", shininess);

    if (textures.size() == 0) {
        shader.uploadFloat("uUseTexture", 0.0f);
    } else {
        shader.uploadFloat("uUseTexture", 1.0f);
    }

    for (uint32_t i = 0; i < textures.size(); i++) {
        TextureType texType = textures[i].getType();

        switch (texType) {
            // see texPhong.frag file
            case TextureType_DIFFUSE:
                textures[i].bind(GL_TEXTURE0);
                break;
            case TextureType_SPECULAR:
                textures[i].bind(GL_TEXTURE1);
                break;
            default:
                std::cout << "texture is not a diffuse or specular texture" << std::endl;
                break;
        }
    }

    shader.uploadMat4("uModel", model);
    shader.uploadMat3("uInverseModel", inverseModel);

    Renderer::draw(*vao, *ibo, shader);
}