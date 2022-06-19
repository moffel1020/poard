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
    ~Window();
    void ChangeTitle(std::string title);
    void Initialize();
    void Close();
private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

