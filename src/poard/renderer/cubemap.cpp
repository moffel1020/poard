#include "cubemap.h"

Cubemap::Cubemap(const std::string& directory) {
    std::vector<std::string> faces {
        directory + "right.jpg",
        directory + "left.jpg",
        directory + "top.jpg",
        directory + "bottom.jpg",
        directory + "front.jpg",
        directory + "back.jpg",
    };

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    stbi_set_flip_vertically_on_load(false);

    for (uint32_t i = 0; i < faces.size(); i++) {
        std::cout << "loading cubemap face: " << faces[i] << std::endl;
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &comp, 0);

        GLenum format; 
        switch (comp) {
            case 1: format = GL_RED;    break;
            case 3: format = GL_RGB;    break;
            case 4: format = GL_RGBA;   break;
        }

        if (!data) {
            std::cout << "cubemap face " << faces[i] << " failed to load" << std::endl;
            return;
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    vao = std::make_unique<VertexArray>();
    vbo = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    ibo = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));

    vao->addBuffer(*vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
}


void Cubemap::draw(Shader& shader) {
    glm::mat4 view = Application::get().getActiveScene()->getActiveCam()->getViewMatrix();
    glm::mat4 proj = Application::get().getActiveScene()->getActiveCam()->getProjMatrix();
    view = glm::mat4(glm::mat3(view));

    glDepthFunc(GL_LEQUAL);
    shader.bind();
    shader.uploadMat4("uView", view);
    shader.uploadMat4("uProjection", proj);
    bind();
    Renderer::draw(*vao, *ibo, shader);
    glDepthFunc(GL_LESS);
}

void Cubemap::bind(uint32_t slot) {
    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}