#pragma once
#include "poard.h"

class CubeScene : public Scene
{
public:
    using Scene::Scene;
    void start() override;
    void update(float dt) override;
    void draw() override;
private:
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Camera> cam;
    std::unique_ptr<Texture> tex; 
    std::unique_ptr<VertexArray> vao; 
    std::unique_ptr<VertexBuffer> vbo;
    std::unique_ptr<IndexBuffer> ibo;
};