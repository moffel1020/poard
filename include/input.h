#pragma once
#include "core.h"

namespace Input
{
    void Initialize(GLFWwindow* window);
    bool isMouseButtonDown(int button);
    bool isKeyDown(int key);
    float getMouseXOffset();
    float getMouseYOffset();
}