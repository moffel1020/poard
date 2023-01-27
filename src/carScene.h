#pragma once
#include "poard.h"

class CarScene : public Scene
{
public:
    using Scene::Scene;
    void start() override;
    void update(float dt) override;
    void draw() override;
    void gui() override;
private:
    std::unique_ptr<Model> ground;
    std::unique_ptr<Cubemap> skybox;
    std::unique_ptr<Shader> modelShader;
    std::unique_ptr<Shader> skyShader;
    std::vector<PointLight> pointLights;
    std::vector<SpotLight> spotLights;

    std::unique_ptr<Model> car;
    std::unique_ptr<Model> leftWheel;
    std::unique_ptr<Model> rightWheel;
    float steeringAngle = 0.0f;

    glm::vec3 blWheelPos = glm::vec3(2.0f, 0.5f, 1.1f);
    glm::vec3 flWheelPos = glm::vec3(-1.788f, 0.5f, 1.1f);
    glm::vec3 brWheelPos = glm::vec3(2.0f, 0.5f, -1.1f);
    glm::vec3 frWheelPos = glm::vec3(-1.788f, 0.5f, -1.1f);
};