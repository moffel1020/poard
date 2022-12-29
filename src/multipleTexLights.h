#pragma once
#include "poard.h"

class MultipleTexLights : public Scene
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
    std::unique_ptr<Texture> cubeDiff;
    std::unique_ptr<Texture> cubeSpec;
    glm::vec3 pLightPos = glm::vec3(4.0f, 2.0f, 0.0f);
    glm::vec3 sLightPos = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 sLightDir = glm::vec3(0.0f, 0.0f, -1.0f);
};