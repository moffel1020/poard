#pragma once
#include "core.h"

class Texture
{
public:
    Texture(const std::string& file);
    void bind();
    void unbind();

private:
    uint32_t id;
    int width;
    int height;
    int comp;
};