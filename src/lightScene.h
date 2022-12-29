#pragma once
#include "poard.h"

class LightScene : public Scene
{
public:
    using Scene::Scene;
    void start() override;
    void update(float dt) override;
    void draw() override;
    void gui() override;
private:
    std::unique_ptr<Shader> modelShader;
    std::unique_ptr<Shader> lightShader;
    std::unique_ptr<Camera> cam;
    std::unique_ptr<VertexArray> cubeVao; 
    std::unique_ptr<VertexBuffer> cubeVbo;
    std::unique_ptr<IndexBuffer> cubeIbo;
    glm::vec3 lightPos = glm::vec3(4.0f, 2.0f, 0.0f);
    glm::vec3 lightAmbient = glm::vec3(0.2f, 0.2f, 0.2f);
    glm::vec3 lightDiffuse = glm::vec3(1.0f, 1.0f, 1.0f);
};