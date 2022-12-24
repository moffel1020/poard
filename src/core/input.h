#pragma once

class Input
{
public:
    static void init();
    static void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
    static bool isMouseButtonDown(int button);
    static bool isKeyDown(int key);
    static int getMouseXPos();
    static int getMouseYPos();
    static void update();
    static int getMouseXMovement();
    static int getMouseYMovement();
private:
    inline static int lastXPos;
    inline static int lastYPos;
};