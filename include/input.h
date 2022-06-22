#pragma once

namespace Input
{
    void initialize(GLFWwindow* window);
    bool isMouseButtonDown(int button);
    bool isKeyDown(int key);
    float getMouseXOffset();
    float getMouseYOffset();
}