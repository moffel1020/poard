#pragma once
#include <fstream>
#include <string>
#include "core.h"

class Shader
{
public:
    Shader(const std::string& vertFilepath, const std::string& fragFilepath);
    ~Shader();
    void bind();
    uint32_t getUniformLocation(const char* name);
    void uploadFloat(const char* name, float f);
    void uploadInt(const char* name, int i);
    void uploadVec3(const char* name, const glm::vec3& vec3);
    void uploadVec3(const char* name, float x, float y, float z);
    void uploadMat4(const char* name, const glm::mat4& mat4);
private:
    std::string parseShader(const std::string& filepath);
    uint32_t compileShader(unsigned int type, const std::string& filePath);
    uint32_t id;
};