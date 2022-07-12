#pragma once
#include "GLFW/glfw3.h"

class Input
{
public:
    bool isMouseButtonDown(int button);
    bool isKeyDown(int key);
    int getMouseXPos();
    int getMouseYPos();
};
