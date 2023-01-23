#pragma once
#include "core.h"
#include "mesh.h"
#include "texture.h"

class Model
{
public:
    Model(std::string path);
    void draw(Shader& shader);

private:
    std::vector<Mesh> meshes;
    std::string directory;

    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* node, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType aiType, TextureType type);
};