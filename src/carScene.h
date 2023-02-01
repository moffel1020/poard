#pragma once
#include "poard.h"
#include "car.h"

class CarScene : public Scene
{
public:
    using Scene::Scene;
    void start() override;
    void update(float dt) override;
    void draw() override;
    void gui() override;
private:

    std::unique_ptr<Car> car;
    //Car car;
    Camera carCam = Camera(glm::vec3(0.0f, 0.0f, 0.0f), 80.0f);

    std::unique_ptr<Model> ground;
    std::unique_ptr<Cubemap> skybox;
    std::unique_ptr<Shader> modelShader;
    std::unique_ptr<Shader> skyShader;
    std::vector<PointLight> pointLights;
    std::vector<SpotLight> spotLights;
};