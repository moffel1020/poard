#pragma once
#include "core.h"

enum TextureType {
    TextureType_DIFFUSE,
    TextureType_SPECULAR,
    TextureType_UNKNOWN
};

class Texture
{
public:
    Texture(int width, int height);
    Texture(const std::string& file, TextureType texType=TextureType_UNKNOWN);
    void bind(uint32_t slot = GL_TEXTURE0);
    void unbind();
    void setData(void* data, uint32_t size);
    TextureType getType() { return type; }
    const std::string& getPath() { return path; }

private:
    uint32_t id;
    std::string path;
    TextureType type;
    int width;
    int height;
    int comp;
};