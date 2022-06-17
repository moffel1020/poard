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
private:
	std::string ParseShader(const char* filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
};