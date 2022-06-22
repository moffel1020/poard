#include "core.h"
#include "window.h"


Window::Window(int width, int height, const char *title, bool fullscreen, bool lockCursor)
{
    this->width = width;
    this->height = height;
    this->title = title;
    this->fullscreen = fullscreen;
    this->lockCursor = lockCursor;
}

void Window::Initialize()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor *monitor = (fullscreen) ? glfwGetPrimaryMonitor() : nullptr;
    GLwindow = glfwCreateWindow(width, height, title, monitor, nullptr);
    glfwSetFramebufferSizeCallback(this->GLwindow, Window::framebuffer_size_callback);

    if (GLwindow == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
    }
    
    glfwMakeContextCurrent(GLwindow);

    if (lockCursor) LockCursor();
    else ShowCursor();
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
    glfwDestroyWindow(GLwindow);
}

void Window::LockCursor()
{
    glfwSetInputMode(GLwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    lockCursor = true;
}

void Window::ShowCursor()
{
    glfwSetInputMode(GLwindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    lockCursor = false;
}