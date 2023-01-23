#include "model.h"
#include "assimp/material.h"
#include "texture.h"


Model::Model(std::string path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "assimp error: " << importer.GetErrorString() << std::endl;
        return;
    }

    path.find("\\") != std::string::npos ? 
        directory = path.substr(0, path.find_last_of('\\')) :
        directory = path.substr(0, path.find_last_of('/'));
    
    std::cout << "loading model from directory:\n\t" << directory << std::endl;
    
    processNode(scene->mRootNode, scene);
}


void Model::draw(Shader& shader) {
    for (uint32_t i = 0; i < meshes.size(); i++) {
        meshes[i].draw(shader);
    }
}


void Model::processNode(aiNode* node, const aiScene* scene) {
    for (uint32_t i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for (uint32_t i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}


Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
        glm::vec2 texCoord;
        mesh->mTextureCoords[0] ?   // check if mesh has texture coordinates 
            texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y) :
            texCoord = glm::vec2();

        Vertex vertex {
            glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),
            glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z),
            texCoord
        };

        vertices.push_back(vertex);
    }

    for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (uint32_t j = 0; j < mesh->mNumFaces; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType_SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}


std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType aiType, TextureType type) {
    std::vector<Texture> textures;

    for (uint32_t i = 0; i < mat->GetTextureCount(aiType); i++) {
        aiString str;
        mat->GetTexture(aiType, i, &str);
        textures.emplace_back(str.C_Str(), type);
    }

    return textures;
}