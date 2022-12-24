#pragma once
#include "core.h"
#include "scene.h"
#include "cubeScene.h"
#include "window.h"
#include "renderer.h"
#include "buffers.h"
#include "gui.h"


class Application
{
public:
    Application();
    void run();

    void addScene(Scene* scene);
    void setScene(const std::string& name);

    Window& getWindow() { return *window; }
    static Application& getInstance() { return *instance; }
private:
    std::unique_ptr<Window> window;
    static Application* instance;
    std::string activeScene;
    std::unordered_map<std::string, Scene*> scenes;
};