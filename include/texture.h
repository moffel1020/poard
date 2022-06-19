#pragma once

class Texture
{
public:
    Texture(const char* file);
    void Bind();
    void Unbind();

private:
    unsigned int id;
    int width;
    int height;
    int comp;
};