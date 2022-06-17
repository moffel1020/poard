#pragma once
#include "core.h"

class Window
{
public:
    GLFWwindow *GLwindow;
    int width;
    int height;
    int refreshRate;
    const char *title;
    bool fullscreen;

    explicit Window(int width, int height, int refreshRate, const char *title, bool fullscreen);
    void ChangeTitle(std::string title);
    void Initialize();
    void Close();
    void Destroy();
private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

