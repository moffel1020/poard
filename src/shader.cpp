#include <fstream>
#include "core.h"
#include "shader.h"


std::string Shader::parseShader(const std::string& filepath)
{
    std::ifstream file(filepath);
    std::string shader;
    std::string line;
    
    while (getline(file, line))
        shader += line + "\n";

    return shader;
}

uint32_t Shader::compileShader(unsigned int type, const std::string& filePath)
{
    std::string source = parseShader(filePath);
    unsigned int shaderID = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shaderID, 1, &src, nullptr);
    glCompileShader(shaderID);


    char info[1024];
    int compiledSuccesfully;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiledSuccesfully);
    if (compiledSuccesfully == GL_FALSE) {
        glGetShaderInfoLog(shaderID, 1024, NULL, info);
        std::cout << "Shader " << filePath << " failed to compile\n" << info << std::endl;
    }

    return shaderID;
}


Shader::Shader(const std::string& vertFilepath, const std::string& fragFilepath)
{
    this->id = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertFilepath);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragFilepath);

    glAttachShader(id, vs);
    glAttachShader(id, fs);
    glLinkProgram(id);

    int linkingSuccesfull;
    char info[1024];
    glGetProgramiv(id, GL_LINK_STATUS, &linkingSuccesfull);
    if (linkingSuccesfull == GL_FALSE) {
        glGetShaderInfoLog(id, 1024, NULL, info);
        std::cout << "Shader " << vertFilepath << " and " << fragFilepath << " failed to link\n" << info << std::endl;
        glDeleteProgram(id);
    }

    glValidateProgram(id);
    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Shader::activate()
{
    glUseProgram(id);
}

Shader::~Shader()
{
    glDeleteProgram(id);
}

unsigned int Shader::getUniformLocation(const char* name)
{
    return glGetUniformLocation(id, name);
}

void Shader::uploadFloat(const char* name, float f)
{
    glUniform1f(getUniformLocation(name), f);
}

void Shader::uploadVec3(const char* name, glm::vec3& vec3)
{
    glUniform3f(getUniformLocation(name), vec3.x, vec3.y, vec3.z);
}

void Shader::uploadMat4(const char* name, glm::mat4& mat4)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat4));
}