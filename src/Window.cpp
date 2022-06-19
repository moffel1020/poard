#include "core.h"
#include "window.h"


Window::Window(int width, int height, int refreshRate, const char *title, bool fullscreen)
{
    this->width = width;
    this->height = height;
    this->refreshRate = refreshRate;
    this->title = title;
    this->fullscreen = fullscreen;
}

void Window::Initialize()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor *monitor = (fullscreen) ? glfwGetPrimaryMonitor() : nullptr;
    GLwindow = glfwCreateWindow(width, height, title, monitor, nullptr);
    glfwSetFramebufferSizeCallback(this->GLwindow, Window::framebuffer_size_callback);

    if (GLwindow == nullptr)
    {
        printf("Failed to create window\n");
        glfwTerminate();
    }
    glfwMakeContextCurrent(GLwindow);
}

void Window::ChangeTitle(std::string title)
{
    glfwSetWindowTitle(GLwindow, title.c_str());
    this->title = title.c_str();
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // TODO: actually update width and height variables of window
    glViewport(0, 0, width, height);
}

void Window::Close()
{
    glfwSetWindowShouldClose(GLwindow, true);
}

Window::~Window()
{
    glfwDestroyWindow(this->GLwindow);
}