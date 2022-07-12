#include "core.h"
#include "input.h"
#include "application.h"

bool Input::isMouseButtonDown(int button)
{
    GLFWwindow* nativeWindow = Application::getInstance().getWindow()->getNativeWindow();
    return glfwGetMouseButton(nativeWindow, button);
}

bool Input::isKeyDown(int key)
{
    GLFWwindow* nativeWindow = Application::getInstance().getWindow()->getNativeWindow();
    return glfwGetKey(nativeWindow, key);
}

int Input::getMouseXPos()
{
    GLFWwindow* nativeWindow = Application::getInstance().getWindow()->getNativeWindow();
    double xpos;
    glfwGetCursorPos(nativeWindow, &xpos, nullptr);
    return xpos;
}

int Input::getMouseYPos()
{
    GLFWwindow* nativeWindow = Application::getInstance().getWindow()->getNativeWindow();
    double ypos;
    glfwGetCursorPos(nativeWindow, nullptr, &ypos);
    return ypos;
}
