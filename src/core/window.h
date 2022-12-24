#pragma once
#include "core.h"

class Window
{
public:
    Window(uint32_t width, uint32_t height, const std::string& title, bool fullscreen, bool lockCursor, bool enableVsync=false);
    ~Window();
    void changeTitle(std::string title);
    void close();
    void setCursorMode(bool locked);
    void setVsync(bool enableVsync);
    bool getLockCursor() { return lockCursor; }
    uint32_t getWidth() { return width; }
    uint32_t getHeight() { return height; }
    GLFWwindow* getNativeWindow() { return nativeWindow; }
private:
    std::string title;
    bool lockCursor;
    bool enableVsync;
    GLFWwindow* nativeWindow;
    uint32_t width;
    uint32_t height;
    bool fullscreen;
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
