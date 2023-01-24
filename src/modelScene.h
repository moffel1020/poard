#pragma once
#include "buffers.h"
#include "poard.h"

class ModelScene : public Scene
{
public:
    using Scene::Scene;
    void start() override;
    void update(float dt) override;
    void draw() override;
    void gui() override;
private:
    std::unique_ptr<Model> model;
    std::unique_ptr<Shader> modelShader;
    std::unique_ptr<Camera> cam;
    std::vector<PointLight> pointLights;
    std::vector<SpotLight> spotLights;
};