#include "lightScene.h"


void LightScene::start() {
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f, 
        0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f,
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


    this->cubeVao = std::make_unique<VertexArray>();
    this->cubeVbo = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    this->cubeIbo = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));
    this->cam = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f), 70.0f);
    this->modelShader = std::make_unique<Shader>("./res/shader/default.vert", "./res/shader/light.frag");
    this->lightShader = std::make_unique<Shader>("./res/shader/default.vert", "./res/shader/white.frag");
    // this->crateTex = std::make_unique<Texture>("./res/texture/crate.jpg");
    // this->whiteTex = std::make_unique<Texture>(1, 1);

    // uint32_t whiteData = 0xffffffff;
    // whiteTex->setData(&whiteData, sizeof(uint32_t));
    
    cubeVao->addBuffer(*cubeVbo, 0, 3, GL_FLOAT, sizeof(float) * 3, (void*)0);
}

void LightScene::update(float dt) {
    const float speed = 2.0f;
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

    if (Application::get().getWindow()->getLockCursor())
        cam->rotate(Input::getMouseXMovement() * sensitivity, -Input::getMouseYMovement() * sensitivity);
}

void LightScene::draw() {
    cam->update();

    // tex->bind();
    modelShader->bind();

    glm::mat4 view = cam->getViewMatrix();
    glm::mat4 proj = cam->getProjMatrix();
    modelShader->uploadMat4("uProjection", proj);
    modelShader->uploadMat4("uView", view);


    glm::mat4 model = glm::mat4(1.0f);
    modelShader->uploadMat4("uModel", model);
    glm::vec3 objectColor = glm::vec3(0.0f, 0.0f, 1.0f);
    modelShader->uploadVec3("uObjectColor", objectColor);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 0.2f);
    modelShader->uploadVec3("uLightColor", lightColor);
    Renderer::draw(*cubeVao, *cubeIbo, *modelShader);

    lightShader->bind();
    lightShader->uploadMat4("uProjection", proj);
    lightShader->uploadMat4("uView", view);

    model = glm::translate(glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f)), glm::vec3(4.0f, 2.0f, 0.0f));
    lightShader->uploadMat4("uModel", model);
    Renderer::draw(*cubeVao, *cubeIbo, *lightShader);

    // whiteTex->bind();
}

void LightScene::gui() {
    ImGui::Begin("Hello, world!");
    ImGui::Text("App: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}