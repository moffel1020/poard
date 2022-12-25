#pragma once
#include "core.h"

class Texture
{
public:
    Texture(int width, int height);
    Texture(const std::string& file);
    void bind();
    void unbind();
    void setData(void* data, uint32_t size);

private:
    uint32_t id;
    int width;
    int height;
    int comp;
};