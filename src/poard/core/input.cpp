#include "core.h"
#include "input.h"
#include "application.h"

void Input::init() {
    glfwSetKeyCallback(Application::get().getWindow()->getNativeWindow(), Input::onKeyEvent);
}

void Input::onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // lock or release mouse cursor with ESC key
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        bool isLocked = Application::get().getWindow()->getLockCursor();
        Application::get().getWindow()->setCursorMode(!isLocked);
    }
}

bool Input::isMouseButtonDown(int button) {
    GLFWwindow* nativeWindow = Application::get().getWindow()->getNativeWindow();
    return glfwGetMouseButton(nativeWindow, button);
}

bool Input::isKeyDown(int key) {
    GLFWwindow* nativeWindow = Application::get().getWindow()->getNativeWindow();
    return glfwGetKey(nativeWindow, key);
}

int Input::getMouseXPos() {
    GLFWwindow* nativeWindow = Application::get().getWindow()->getNativeWindow();
    double xpos;
    glfwGetCursorPos(nativeWindow, &xpos, nullptr);
    return xpos;
}

int Input::getMouseYPos() {
    GLFWwindow* nativeWindow = Application::get().getWindow()->getNativeWindow();
    double ypos;
    glfwGetCursorPos(nativeWindow, nullptr, &ypos);
    return ypos;
}

int Input::getMouseXMovement() {
    if (!lastXPos)
        lastYPos = getMouseXPos();

    return getMouseXPos() - lastXPos;
}

int Input::getMouseYMovement() {
    if (!lastYPos)
        lastYPos = getMouseYPos();

    return Input::getMouseYPos() - lastYPos;
}

void Input::update() {
    lastXPos = getMouseXPos();
    lastYPos = getMouseYPos();
}