#pragma once

class Window
{
public:
    GLFWwindow *GLwindow;
    uint32_t width;
    uint32_t height;
    const char *title;
    bool fullscreen;

    explicit Window(uint32_t width, uint32_t height, const char *title, bool fullscreen, bool lockCursor);
    ~Window();
    void changeTitle(std::string title);
    void close();
    void showCursor();
    void lockCursor();
private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};