#pragma once
#include <fstream>
#include "core.h"


class Shader
{
public:
    unsigned int id;
    Shader(const char* vertFilepath, const char* fragFilepath);
    void Activate();
    void Delete();
    unsigned int GetUniformLocation(const char* name);
    void UploadFloat(const char* name, float f);
    void UploadVec3(const char* name, glm::vec3& vec3);
    void UploadMat4(const char* name, glm::mat4& mat4);
private:
    std::string ParseShader(const char* filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
};