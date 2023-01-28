#pragma once
#include "core.h"
#include "scene.h"
#include "input.h"
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
    Scene* getActiveScene() { return scenes[activeScene]; }

    float getFrameTime() { return frameTime; }
    Window* getWindow() { return window; }
    static Application& get() { return *instance; }
private:
    Window* window;
    static Application* instance;
    std::string activeScene;
    std::unordered_map<std::string, Scene*> scenes;

    float frameTime = 0.0f;
    float accum = 0.0f;
    float fixedDeltaTime = 0.001f;
};