#include "core.h"
#include "input.h"

namespace Input
{
    bool pressedKeys[GLFW_KEY_LAST] = { };
    bool pressedMouseButtons[GLFW_MOUSE_BUTTON_LAST] = { };
    float mouseX = 0;
    float mouseY = 0;
    float OffsetX = 0;
    float OffsetY = 0;
    float scrollX = 0;
    float scrollY = 0;


    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_RELEASE) {
            pressedKeys[key] = false;
            return;
        }

        pressedKeys[key] = true;
    }


    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        pressedMouseButtons[button] = action == GLFW_PRESS;
    }


    void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
        OffsetX = xpos - mouseX;
        OffsetY = mouseY - ypos;

        mouseX = xpos;
        mouseY = ypos;
    }


    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        scrollX = xoffset;
        scrollY = yoffset;
    }


    void initialize(GLFWwindow* window)
    {
        glfwSetKeyCallback(window, key_callback);
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        glfwSetCursorPosCallback(window, cursor_position_callback);
        glfwSetScrollCallback(window, scroll_callback);
    }


    bool isKeyDown(int key)
    {
        if (pressedKeys[key]) 
            return true;

        return false;
    }


    bool isMouseButtonDown(int button)
    {
        if (pressedMouseButtons[button])
            return true;

        return false;
    }

    float getMouseXOffset() {
        float offset = OffsetX;
        OffsetX = 0;
        return offset;
    }

    float getMouseYOffset() {
        float offset = OffsetY;
        OffsetY = 0;
        return offset;
    }
}