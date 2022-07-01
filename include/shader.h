#pragma once

class Shader
{
public:
    Shader(const std::string& vertFilepath, const std::string& fragFilepath);
    ~Shader();
    void activate();
    uint32_t getUniformLocation(const char* name);
    void uploadFloat(const char* name, float f);
    void uploadVec3(const char* name, glm::vec3& vec3);
    void uploadMat4(const char* name, glm::mat4& mat4);
private:
    std::string parseShader(const std::string& filepath);
    uint32_t compileShader(unsigned int type, const std::string& filePath);
    uint32_t id;
};