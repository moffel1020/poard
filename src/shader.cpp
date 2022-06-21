#include <fstream>
#include "core.h"
#include "shader.h"


std::string Shader::ParseShader(const char* filepath)
{
    std::ifstream file(filepath);
    std::string shader;
    std::string line;
    
    while (getline(file, line))
        shader += line + "\n";

    return shader;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& filePath)
{
    std::string source = ParseShader(filePath.c_str());
    unsigned int shaderID = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shaderID, 1, &src, nullptr);
    glCompileShader(shaderID);


    // check compile errors
    char info[1024];
    int compiledSuccesfully;

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiledSuccesfully);
    if (compiledSuccesfully == GL_FALSE) {
        glGetShaderInfoLog(shaderID, 1024, NULL, info);
        std::cout << "Shader " << filePath << " failed to compile\n" << info << std::endl;
    }

    return shaderID;
}


Shader::Shader(const char* vertFilepath, const char* fragFilepath)
{
    this->id = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertFilepath);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragFilepath);

    glAttachShader(id, vs);
    glAttachShader(id, fs);
    glLinkProgram(id);

    //check for linking errors
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

void Shader::Activate()
{
    glUseProgram(id);
}

Shader::~Shader()
{
    glDeleteProgram(id);
}

unsigned int Shader::GetUniformLocation(const char* name)
{
    return glGetUniformLocation(id, name);
}

void Shader::UploadFloat(const char* name, float f)
{
    glUniform1f(GetUniformLocation(name), f);
}

void Shader::UploadVec3(const char* name, glm::vec3& vec3)
{
    glUniform3f(GetUniformLocation(name), vec3.x, vec3.y, vec3.z);
}

void Shader::UploadMat4(const char* name, glm::mat4& mat4)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat4));
}