#pragma once
#include "core.h"

enum TextureType {
    DIFFUSE,
    SPECULAR
};

class Texture
{
public:
    Texture(int width, int height);
    Texture(const std::string& file);
    void bind(uint32_t slot = GL_TEXTURE0);
    void unbind();
    void setData(void* data, uint32_t size);
    TextureType getType() { return texType; }

private:
    uint32_t id;
    TextureType texType;
    int width;
    int height;
    int comp;
};