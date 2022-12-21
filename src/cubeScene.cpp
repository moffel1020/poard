#include "cubeScene.h"
#include "renderer.h"
#include "input.h"

CubeScene::CubeScene() {
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    };

    uint32_t indices[] = {
        0, 1, 2,
        0, 2, 3,
        4, 5, 6,
        4, 6, 7,
        8, 9, 10,
        8, 10, 11,
        12, 13, 14,
        12, 14, 15,
        16, 17, 18,
        16, 18, 19,
        20, 21, 22,
        20, 22, 23
    };


    this->vao = std::make_unique<VertexArray>();
    this->vbo = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    this->ibo = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));
    this->cam = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f), 70.0f);
    this->shader = std::make_unique<Shader>("./res/shader/default.vert", "./res/shader/default.frag");
    this->tex = std::make_unique<Texture>("./res/texture/crate.jpg");
    
    vao->addBuffer(*vbo, 0, 3, GL_FLOAT, sizeof(float) * 5, (void*)0);                    // positions
    vao->addBuffer(*vbo, 1, 2, GL_FLOAT, sizeof(float) * 5, (void*)(sizeof(float) * 3));  // texture coordinates
}

void CubeScene::update(float dt) {
    const float speed = 1.0f;
    const float sensitivity = 0.1f;

    if (Input::isKeyDown(GLFW_KEY_W))
        cam->move(FORWARD, speed * dt);
    if (Input::isKeyDown(GLFW_KEY_S))
        cam->move(BACKWARD, speed * dt);
    if (Input::isKeyDown(GLFW_KEY_D))
        cam->move(RIGHT, speed * dt);
    if (Input::isKeyDown(GLFW_KEY_A))
        cam->move(LEFT, speed * dt);
    if (Input::isKeyDown(GLFW_KEY_SPACE))
        cam->move(UP, speed * dt);
    if (Input::isKeyDown(GLFW_KEY_LEFT_SHIFT))
        cam->move(DOWN, speed * dt);

    cam->rotate(Input::getMouseXMovement() * sensitivity, -Input::getMouseYMovement() * sensitivity);
}

void CubeScene::draw() {
    glm::mat4 model = glm::mat4(1.0f);
    vao->bind();

    cam->update();

    tex->bind();
    shader->bind();
    glm::mat4 view = cam->getViewMatrix();
    glm::mat4 proj = cam->getProjMatrix();
    shader->uploadMat4("uModel", model);
    shader->uploadMat4("uProjection", proj);
    shader->uploadMat4("uView", view);
    Renderer::draw(*vao, *ibo, *shader);
}