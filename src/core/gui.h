#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class Gui
{
public:
    Gui();
    void begin();
    void end();
    ~Gui();
};
