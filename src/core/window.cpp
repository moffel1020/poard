#include "core.h"
#include "window.h"
#include "application.h"

Window::Window(uint32_t width, uint32_t height, const std::string& title, bool fullscreen, bool lockCursor, bool enableVsync) {
    this->width = width;
    this->height = height;
    this->title = title;
    this->fullscreen = fullscreen;
    this->lockCursor = lockCursor;
    this->enableVsync = enableVsync;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor *monitor = (fullscreen) ? glfwGetPrimaryMonitor() : nullptr;
    nativeWindow = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
    glfwSetFramebufferSizeCallback(this->nativeWindow, Window::framebuffer_size_callback);

    if (nativeWindow == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
    }
    
    glfwMakeContextCurrent(nativeWindow);

    setCursorMode(lockCursor);
    setVsync(enableVsync);
}

void Window::changeTitle(std::string title) {
    glfwSetWindowTitle(nativeWindow, title.c_str());
    this->title = title;
}

void Window::framebuffer_size_callback(GLFWwindow* nativeWindow, int width, int height) {
    Window* window = Application::getInstance().getWindow();
    window->width = width;
    window->height = height;
    glViewport(0, 0, width, height);
}

void Window::close() {
    glfwSetWindowShouldClose(nativeWindow, true);
}

Window::~Window() {
    glfwDestroyWindow(nativeWindow);
}

void Window::setCursorMode(bool locked) {
    this->lockCursor = locked;
    glfwSetInputMode(nativeWindow, GLFW_CURSOR, locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void Window::setVsync(bool enableVsync) {
    this->enableVsync = enableVsync;
    enableVsync ? glfwSwapInterval(1) : glfwSwapInterval(0);
}
