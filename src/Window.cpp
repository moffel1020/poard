#include "core.h"
#include "window.h"


Window::Window(uint32_t width, uint32_t height, const std::string& title, bool fullscreen, bool lockCursor)
{
    this->width = width;
    this->height = height;
    this->title = title;
    this->fullscreen = fullscreen;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor *monitor = (fullscreen) ? glfwGetPrimaryMonitor() : nullptr;
    GLwindow = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
    glfwSetFramebufferSizeCallback(this->GLwindow, Window::framebuffer_size_callback);

    if (GLwindow == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
    }
    
    glfwMakeContextCurrent(GLwindow);

    if (lockCursor) this->lockCursor();
    else showCursor();
}

void Window::changeTitle(std::string title)
{
    glfwSetWindowTitle(GLwindow, title.c_str());
    this->title = title;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // TODO: make it so window object width and height also change
    glViewport(0, 0, width, height);
}

void Window::close()
{
    glfwSetWindowShouldClose(GLwindow, true);
}

Window::~Window()
{
    glfwDestroyWindow(GLwindow);
}

void Window::lockCursor()
{
    glfwSetInputMode(GLwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::showCursor()
{
    glfwSetInputMode(GLwindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}