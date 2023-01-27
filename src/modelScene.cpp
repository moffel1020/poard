#include "modelScene.h"
#include "GLFW/glfw3.h"
#include "glm/ext/scalar_constants.hpp"


void ModelScene::start() {
    Camera* cam = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), 70.0f);
    setActiveCam(cam);

    this->modelShader = std::make_unique<Shader>("./res/shader/phong.vert", "./res/shader/phong.frag");
    this->skyShader = std::make_unique<Shader>("./res/shader/skybox.vert", "./res/shader/skybox.frag");

    this->car = std::make_unique<Model>("./res/models/car/hull.obj");
    this->rightWheel = std::make_unique<Model>("./res/models/car/wheel_r.obj");
    this->leftWheel = std::make_unique<Model>("./res/models/car/wheel_l.obj");
    this->ground = std::make_unique<Model>("./res/models/ground/ground.obj");

    this->skybox = std::make_unique<Cubemap>("./res/texture/skybox/");
}


void ModelScene::update(float dt) {
    const float speed = 4.0f;
    const float sensitivity = 0.1f;

    if (Input::isKeyDown(GLFW_KEY_W))
        activeCam->move(FORWARD, speed * dt);
    if (Input::isKeyDown(GLFW_KEY_S))
        activeCam->move(BACKWARD, speed * dt);
    if (Input::isKeyDown(GLFW_KEY_D))
        activeCam->move(RIGHT, speed * dt);
    if (Input::isKeyDown(GLFW_KEY_A))
        activeCam->move(LEFT, speed * dt);
    if (Input::isKeyDown(GLFW_KEY_SPACE))
        activeCam->move(UP, speed * dt);
    if (Input::isKeyDown(GLFW_KEY_LEFT_SHIFT))
        activeCam->move(DOWN, speed * dt);

    if (Application::get().getWindow()->getLockCursor())
        activeCam->rotate(Input::getMouseXMovement() * sensitivity, -Input::getMouseYMovement() * sensitivity);
}


void ModelScene::draw() {
    activeCam->update();

    modelShader->bind();
    modelShader->uploadMat4("uProjection", activeCam->getProjMatrix());
    modelShader->uploadMat4("uView", activeCam->getViewMatrix());
    modelShader->uploadVec3("uCamPos", activeCam->getPosition());
    modelShader->uploadFloat("uPointLightCount", pointLights.size());
    modelShader->uploadFloat("uSpotLightCount", spotLights.size());

    DirLight dirLight = DirLight(glm::vec3(1.0f, -1.0f, 1.0f));
    dirLight.setDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
    dirLight.setAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
    dirLight.upload(*modelShader);

    for (uint32_t i = 0; i < pointLights.size(); i++)
        pointLights[i].upload(*modelShader, i);

    for (uint32_t i = 0; i < spotLights.size(); i++)
        spotLights[i].upload(*modelShader, i);


    float wheelRot = 2.0f * glm::pi<float>() * sin(glfwGetTime());
    float carRot = (2.0f * glm::pi<float>() * cos(glfwGetTime())) / 4;
    glm::mat4 carTransform(1.0f);
    carTransform = glm::rotate(carTransform, abs(carRot), glm::vec3(0.0f, 1.0f, 0.0f));
    car->draw(*modelShader, carTransform);

    ground->draw(*modelShader);

    glm::mat4 wheelTransform = glm::translate(carTransform, flWheelPos);
    wheelTransform = glm::rotate(wheelTransform, glm::radians(steeringAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    wheelTransform = glm::rotate(wheelTransform, wheelRot, glm::vec3(0.0f, 0.0f, 1.0f));
    leftWheel->draw(*modelShader, wheelTransform);

    wheelTransform = glm::translate(carTransform, frWheelPos);
    wheelTransform = glm::rotate(wheelTransform, glm::radians(steeringAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    wheelTransform = glm::rotate(wheelTransform, wheelRot, glm::vec3(0.0f, 0.0f, 1.0f));
    rightWheel->draw(*modelShader, wheelTransform);

    wheelTransform = glm::translate(carTransform, blWheelPos);
    wheelTransform = glm::rotate(wheelTransform, wheelRot, glm::vec3(0.0f, 0.0f, 1.0f));
    leftWheel->draw(*modelShader, wheelTransform);

    wheelTransform = glm::translate(carTransform, brWheelPos);
    wheelTransform = glm::rotate(wheelTransform, wheelRot, glm::vec3(0.0f, 0.0f, 1.0f));
    rightWheel->draw(*modelShader, wheelTransform);


    skybox->draw(*skyShader);
}


void ModelScene::gui() {
    {
        ImGui::Begin("performance");
        ImGui::Text("App: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        glm::vec3 pos = activeCam->getPosition();
        ImGui::Text("cam x: %.2f", pos.x);
        ImGui::Text("cam y: %.2f", pos.y);
        ImGui::Text("cam z: %.2f", pos.z);
        ImGui::End();
    }

    {
        ImGui::Begin("car");
        ImGui::SliderFloat("Steering angle:", &steeringAngle, -90.0f, 90.0f);
        ImGui::End();
    }
}