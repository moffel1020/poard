#include "lightScene.h"


void LightScene::start() {
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.5f, 0.31f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.5f, 0.31f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.5f, 0.31f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.5f, 0.31f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.5f, 0.31f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.5f, 0.31f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.5f, 0.31f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.5f, 0.31f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.5f, 0.31f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.5f, 0.31f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.5f, 0.31f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.5f, 0.31f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.5f, 0.31f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.5f, 0.31f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.5f, 0.31f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.5f, 0.31f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.5f, 0.31f,
    };

    this->cubeVao = std::make_unique<VertexArray>();
    this->cubeVbo = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    // this->cubeIbo = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));
    this->cam = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f), 70.0f);
    this->modelShader = std::make_unique<Shader>("./res/shader/default.vert", "./res/shader/light.frag");
    this->lightShader = std::make_unique<Shader>("./res/shader/default.vert", "./res/shader/white.frag");
    this->crateTex = std::make_unique<Texture>("./res/texture/crate.jpg");
    this->whiteTex = std::make_unique<Texture>(1, 1);

    uint32_t whiteData = 0xffffffff;
    whiteTex->setData(&whiteData, sizeof(uint32_t));
    
    cubeVao->addBuffer(*cubeVbo, 0, 3, GL_FLOAT, sizeof(float) * 9, (void*)0);
    cubeVao->addBuffer(*cubeVbo, 1, 3, GL_FLOAT, sizeof(float) * 9, (void*)(sizeof(float) * 3));
    cubeVao->addBuffer(*cubeVbo, 2, 3, GL_FLOAT, sizeof(float) * 9, (void*)(sizeof(float) * 6));
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

    modelShader->bind();
    glm::mat4 view = cam->getViewMatrix();
    glm::mat4 proj = cam->getProjMatrix();
    modelShader->uploadMat4("uProjection", proj);
    modelShader->uploadMat4("uView", view);


    glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);
    glm::mat4 model = glm::mat4(1.0f);
    modelShader->uploadMat4("uModel", model);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    modelShader->uploadVec3("uLightColor", lightColor);
    modelShader->uploadVec3("uLightPos", lightPos);
    glm::vec3 camPos = cam->getPosition();
    modelShader->uploadVec3("uCamPos", camPos);
    Renderer::drawTriangles(*cubeVao, *modelShader, 36);

    lightShader->bind();
    lightShader->uploadMat4("uProjection", proj);
    lightShader->uploadMat4("uView", view);

    model = glm::translate(glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f)), lightPos);
    lightShader->uploadMat4("uModel", model);
    Renderer::drawTriangles(*cubeVao, *lightShader, 36);
}

void LightScene::gui() {
    ImGui::Begin("light");
    ImGui::Text("App: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::Text("light position");
    ImGui::SliderFloat("x", &lightX, -10.0f, 10.0f);
    ImGui::SliderFloat("y", &lightY, -10.0f, 10.0f);
    ImGui::SliderFloat("z", &lightZ, -10.0f, 10.0f);

    ImGui::End();
}