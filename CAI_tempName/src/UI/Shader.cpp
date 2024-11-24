#include"caipch.h"
#include "Shader.h"
#include<glad/glad.h>
#include"log/Log.h"
#define ShaderCheck(x) {	int success;char infoLog[512];glGetShaderiv(x, GL_COMPILE_STATUS, &success);\
						if (!success){ glGetShaderInfoLog(x, 512, NULL, infoLog);\
						LogError( "{0}:{1}---ERROR::SHADER::COMPILATION_FAILED---{3}",__FILE__,__LINE__, infoLog);}}

Shader::Shader() :ID(0)
{
}

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath)
{
	if (Load(vertexShaderPath, fragmentShaderPath, geometryShaderPath))
		ComplieShader();
}


Shader::~Shader()
{
}

bool Shader::Load(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath)
{
	LoadShadder(vertexShaderPath, vertexStr);
	if (vertexStr.empty()) {
		LogError("vertex shader str is empty");
		return false;
	}
	LoadShadder(fragmentShaderPath, fragmentStr);
	if (fragmentStr.empty()) {
		LogError("fragment shader str is empty");
		return false;
	}
	LoadShadder(geometryShaderPath, geometryStr);
	return true;
}

void Shader::LoadShadder(const std::string& filePath, std::string& shaderStr)
{
	if (filePath.empty())
		return;
	std::ifstream file(filePath);
	if (!file.is_open()) {
		LogError("There is no such file named:{0}", filePath);
		return;
	}
	std::string str;
	while (std::getline(file, str)) {
		shaderStr += str + "\n";
	}
	file.close();
}

void Shader::ComplieShader()
{
	const char* vertexShaderSource = vertexStr.c_str();
	const char* fragmentShaderSource = fragmentStr.c_str();
	const char* geometryShaderSource = geometryStr.c_str();
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int geometryShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(vertexShader);
	ShaderCheck(vertexShader);
	glCompileShader(fragmentShader);
	ShaderCheck(fragmentShader);
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	if (!geometryStr.empty()) {
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometryShaderSource, NULL);
		glCompileShader(geometryShader);
		ShaderCheck(geometryShader);
		glAttachShader(ID, geometryShader);
		glDeleteShader(geometryShader);
	}
	glLinkProgram(ID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Use() const
{
	glUseProgram(ID);
}


void Shader::SetVec3(const std::string& name, float value, float value2, float value3) const
{
	Use();
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value, value2, value3);
}

void Shader::SetVec4(const std::string& name, float value, float value2, float value3, float value4) const
{
	Use();
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value, value2, value3,value4);
}



void Shader::SetMat4(const std::string& name, const Math::TransMatrix& mat) const
{
	Use();
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const std::string& name, const float* mat) const
{
	Use();
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, mat);
}