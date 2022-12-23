#pragma once

class Input
{
public:
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