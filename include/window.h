#pragma once

class Window
{
public:
    GLFWwindow* GLwindow;
    uint32_t width;
    uint32_t height;
    bool fullscreen;

    Window(uint32_t width, uint32_t height, const std::string& title, bool fullscreen, bool lockCursor, bool enableVsync=false);
    ~Window();
    void changeTitle(std::string title);
    void close();
    void setCursor(bool locked);
    void setVsync(bool enableVsync);
private:
    std::string title;
    bool lockCursor;
    bool enableVsync;
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};