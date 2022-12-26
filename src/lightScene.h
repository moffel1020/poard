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
    std::unique_ptr<Texture> crateTex; 
    std::unique_ptr<Texture> whiteTex;
    std::unique_ptr<VertexArray> cubeVao; 
    std::unique_ptr<VertexBuffer> cubeVbo;
    std::unique_ptr<IndexBuffer> cubeIbo;
};