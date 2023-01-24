#include "modelScene.h"


void ModelScene::start() {
    this->cam = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f), 70.0f);
    this->modelShader = std::make_unique<Shader>("./res/shader/texPhong.vert", "./res/shader/texPhong.frag");
    this->model = std::make_unique<Model>("./res/models/backpack/backpack.obj");

    spotLights.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f), 30.0f, 20.0f);
}

void ModelScene::update(float dt) {
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

    spotLights[0].setPosition(cam->getPosition());
    spotLights[0].setDirection(cam->getDirection());

    if (Application::get().getWindow()->getLockCursor())
        cam->rotate(Input::getMouseXMovement() * sensitivity, -Input::getMouseYMovement() * sensitivity);
}

void ModelScene::draw() {
    cam->update();

    glm::mat4 view = cam->getViewMatrix();
    glm::mat4 proj = cam->getProjMatrix();
    glm::mat4 model(1.0f);

    modelShader->bind();
    modelShader->uploadMat4("uProjection", proj);
    modelShader->uploadMat4("uView", view);
    modelShader->uploadMat4("uModel", model);
    modelShader->uploadVec3("uCamPos", cam->getPosition());
    modelShader->uploadFloat("uPointLightCount", pointLights.size());
    modelShader->uploadFloat("uSpotLightCount", spotLights.size());

    modelShader->uploadFloat("material.shininess", 32.0f);

    DirLight dirLight = DirLight(glm::vec3(0.0f, -1.0f, 0.0f));
    dirLight.upload(*modelShader);

    for (uint32_t i = 0; i < pointLights.size(); i++)
        pointLights[i].upload(*modelShader, i);

    for (uint32_t i = 0; i < spotLights.size(); i++)
        spotLights[i].upload(*modelShader, i);

    this->model->draw(*modelShader);
}

void ModelScene::gui() {
    ImGui::Begin("performance");
    ImGui::Text("App: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}