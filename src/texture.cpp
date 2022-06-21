#include "core.h"
#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Texture::Texture(const char* file)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image_data = stbi_load(file, &width, &height, &comp, 0);

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(image_data);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}