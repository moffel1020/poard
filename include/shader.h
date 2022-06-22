#pragma once

class Shader
{
public:
    uint32_t id;
    Shader(const char* vertFilepath, const char* fragFilepath);
    ~Shader();
    void activate();
    uint32_t getUniformLocation(const char* name);
    void uploadFloat(const char* name, float f);
    void uploadVec3(const char* name, glm::vec3& vec3);
    void uploadMat4(const char* name, glm::mat4& mat4);
private:
    std::string parseShader(const char* filepath);
    unsigned int compileShader(unsigned int type, const std::string& source);
};