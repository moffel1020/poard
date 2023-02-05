#include "carScene.h"
#include "imgui/imgui.h"


void CarScene::start() {
    CarData carData;
    carData.mass = 1632.933f;
    carData.dragConstant = 0.5 * 0.30 * 2.52;
    carData.length = 4.47548;
    carData.width = 1.854f;
    carData.height = 1.410f;
    carData.wheelBase = 2.693f;
    carData.weightRatio = 0.53f;
    carData.automaticTransmission = true;
    carData.finalRatio = 3.46f;
    carData.gearRatios[0] = 4.11f;
    carData.gearRatios[1] = 2.32f;
    carData.gearRatios[2] = 1.54f;
    carData.gearRatios[3] = 1.18f;
    carData.gearRatios[4] = 1.00f;
    carData.gearRatios[5] = 0.85f;
    carData.gearRatios[6] = 3.37f;
    carData.rpmCurve = { 1000.0f, 1500.0f, 2000.0f, 2500.0f, 3000.0f, 3500.0f, 4000.0f, 4500.0f, 5000.0f, 5500.0f, 6000.0f, 6500.0f, 7000.0f, 7500.0f };
    carData.torqueCurve = { 296.0f, 443.9f, 517.9f, 551.0f, 551.0f, 551.0f, 551.0f, 551.0f, 551.0f, 524.0f, 480.6f, 443.7f, 412.0f, 346.1f };

    car = std::make_unique<Car>(carData);

    setActiveCam(&carCam);
    this->modelShader = std::make_unique<Shader>("./res/shader/phong.vert", "./res/shader/phong.frag");
    this->skyShader = std::make_unique<Shader>("./res/shader/skybox.vert", "./res/shader/skybox.frag");
    this->ground = std::make_unique<Model>("./res/models/ground/ground.obj");
    this->skybox = std::make_unique<Cubemap>("./res/texture/skybox/");
}


void CarScene::update(float dt) {
    car->update(dt);
}


void CarScene::draw() {
    if (activeCam == &carCam) {
        const static float sensitivity = 0.1f;

        if (Application::get().getWindow()->getLockCursor())
            activeCam->rotate(Input::getMouseXMovement() * sensitivity, -Input::getMouseYMovement() * sensitivity);

        glm::vec3 pos = car->getPosition();
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

    car->draw(*modelShader);
    ground->draw(*modelShader);
    skybox->draw(*skyShader);
}


void CarScene::gui() {
    ImGui::Begin("performance");
    ImGui::Text("App: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    car->gui();
}
