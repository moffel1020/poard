#pragma once
#include "renderer.h"
#include "window.h"
#include "input.h"

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
