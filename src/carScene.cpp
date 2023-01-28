#include "carScene.h"


void CarScene::start() {
    setActiveCam(&carCam);

    this->modelShader = std::make_unique<Shader>("./res/shader/phong.vert", "./res/shader/phong.frag");
    this->skyShader = std::make_unique<Shader>("./res/shader/skybox.vert", "./res/shader/skybox.frag");

    this->ground = std::make_unique<Model>("./res/models/ground/ground.obj");

    this->skybox = std::make_unique<Cubemap>("./res/texture/skybox/");
}


void CarScene::update(float dt) {
    // if (activeCam == &freeCam) {
    //     const static float speed = 4.0f;
    //     const static float sensitivity = 0.1f;

    //     if (Input::isKeyDown(GLFW_KEY_W))
    //         activeCam->move(FORWARD, speed * dt);
    //     if (Input::isKeyDown(GLFW_KEY_S))
    //         activeCam->move(BACKWARD, speed * dt);
    //     if (Input::isKeyDown(GLFW_KEY_D))
    //         activeCam->move(RIGHT, speed * dt);
    //     if (Input::isKeyDown(GLFW_KEY_A))
    //         activeCam->move(LEFT, speed * dt);
    //     if (Input::isKeyDown(GLFW_KEY_SPACE))
    //         activeCam->move(UP, speed * dt);
    //     if (Input::isKeyDown(GLFW_KEY_LEFT_SHIFT))
    //         activeCam->move(DOWN, speed * dt);

    //     if (Application::get().getWindow()->getLockCursor())
    //         activeCam->rotate(Input::getMouseXMovement() * sensitivity, -Input::getMouseYMovement() * sensitivity);
    // }
    car.update(dt);
}


void CarScene::draw() {
    if (activeCam == &carCam) {
        const static float sensitivity = 0.1f;

        if (Application::get().getWindow()->getLockCursor())
            activeCam->rotate(Input::getMouseXMovement() * sensitivity, -Input::getMouseYMovement() * sensitivity);

        glm::vec3 pos = car.getPosition();
        pos -= activeCam->getDirection() * 5.0f;
        activeCam->setPosition(pos.x, pos.y, pos.z);
    }

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


    car.draw(*modelShader);
    ground->draw(*modelShader);
    skybox->draw(*skyShader);
}


void CarScene::gui() {
    {
        ImGui::Begin("performance");
        ImGui::Text("App: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    car.gui();
}