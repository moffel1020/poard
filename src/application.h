#pragma once
#include "core.h"
#include "scene.h"
#include "cubeScene.h"
#include "window.h"
#include "renderer.h"
#include "buffers.h"

class Application
{
public:
    Application();
    void run();
    Window* getWindow() { return window; }
    static Application& getInstance() { return *instance; }
private:
    Window* window;
    static Application* instance;
};
