#pragma once

class Texture
{
public:
    Texture(const char* file);
    void bind();
    void unbind();

private:
    uint32_t id;
    int width;
    int height;
    int comp;
};