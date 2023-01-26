#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Texture::Texture(int width, int height) {
    this->width = width;
    this->height = height;
    this->comp = 4;     // RGBA
    this->type = TextureType_UNKNOWN;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


Texture::Texture(const std::string& file, TextureType type) {
    this->path = file;
    this->type = type;

    std::cout << "loading texture: " << file << std::endl;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* imageData = stbi_load(file.c_str(), &width, &height, &comp, 0);

    if (!imageData) {
        std::cout << "Texture " << file << " failed to load" << std::endl;
        return;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format; 
    switch (comp) {
        case 1: format = GL_RED;    break;
        case 3: format = GL_RGB;    break;
        case 4: format = GL_RGBA;   break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(imageData);
}


void Texture::setData(void* data, uint32_t size) {
    if (size != width * height * comp) {
        std::cout << "data size does not match texture size" << std::endl;
        return;
    }

    glBindTexture(GL_TEXTURE_2D, id);
    if (comp == 1)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    else if (comp == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    else if (comp == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}


void Texture::bind(uint32_t slot) {
    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D, id);
}


void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}