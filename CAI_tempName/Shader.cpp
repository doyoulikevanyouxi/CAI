#include "Shader.h"
#include<glad/glad.h>
#include"Math.hpp"
#include<fstream>
#include<iostream>

Shader::Shader():isLoad(false),ID(0)
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
}

Shader::Shader(const std::string& shashaFilePathStr):Shader()
{
	load(shashaFilePathStr);
}

Shader::~Shader()
{
}

bool Shader::load(const std::string& shashaFilePathStr)
{
	std::string shaderStr;
	std::string* fileTraget = nullptr;
	std::ifstream fstream(shashaFilePathStr);
	if (!fstream.is_open()) {
		std::cout << "there is no such file:" << shashaFilePathStr << std::endl;
		return false;
	}

	while (std::getline(fstream, shaderStr))
	{

		if (shaderStr == "[vertex_shader]") {
			fileTraget = &vertexshaderStr;
			continue;
		}

		if (shaderStr == "[fragment_shader]") {
			fileTraget = &fragmentshaderStr;
			continue;
		}
		if (fileTraget == nullptr)
			continue;
		shaderStr += "\n";
		fileTraget->append(shaderStr);
	}

	fstream.close();
	fileTraget = nullptr;
	const char* vShaderCode = vertexshaderStr.c_str();
	const char* fShaderCode = fragmentshaderStr.c_str();
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	int success;
	glCompileShader(vertexShader);
	// 打印编译错误（如果有的话）
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::cout << shashaFilePathStr <<":vertex shader compiled fail" << std::endl;
		return false;
	}
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::cout << "fragment shader compiled fail" << std::endl;
		return false;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return true;
}

void Shader::use() const
{
	glUseProgram(ID);
}

void Shader::setVec3(const std::string& name, float value, float value2, float value3) const
{
	use();
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value, value2, value3);
}



void Shader::setMat4(const std::string& name, const Math::TransMatrix& mat) const
{
	use();
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, const float* mat) const
{
	use();
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, mat);
}

float* Shader::getMat4(const std::string& name)
{
	return nullptr;
}
