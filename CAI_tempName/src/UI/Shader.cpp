#include"caipch.h"
#include "Shader.h"
#include<glad/glad.h>

#include "log/Log.h"

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath) :ID(0), vertexShaderPath(vertexShaderPath),
																													 fragmentShaderPath(fragmentShaderPath), 
																													 geometryShaderPath(geometryShaderPath)
{
}


Shader::~Shader()
{
}

bool Shader::Load(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath)
{
	LoadShadder(vertexShaderPath, vertexStr);
	if (vertexStr.empty()) {
		LogError("Vertex string shader can't be empty");
		return false;
	}
	LoadShadder(fragmentShaderPath, fragmentStr);
	if (fragmentStr.empty()) {
		LogError("Fragmen string shader can't be empty");
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

bool Shader::ComplieShader()
{
	if (!Load(vertexShaderPath, fragmentShaderPath, geometryShaderPath))
		return false;
	const char* vertexShaderSource = vertexStr.c_str();
	const char* fragmentShaderSource = fragmentStr.c_str();
	const char* geometryShaderSource = geometryStr.c_str();
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int geometryShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	if (!CheckComplieError(vertexShader)) {
		glDeleteShader(vertexShader);
		return false;
	}
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	if (!CheckComplieError(fragmentShader)) {
		glDeleteShader(fragmentShader);
		return false;
	}
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	if (!geometryStr.empty()) {
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometryShaderSource, NULL);
		glCompileShader(geometryShader);
		if (!CheckComplieError(geometryShader)) {
			glDeleteShader(geometryShader);
			return false;
		}
		glAttachShader(ID, geometryShader);
		glDeleteShader(geometryShader);
	}
	glLinkProgram(ID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return true;
}


inline bool Shader::CheckComplieError(const unsigned int& shader)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << __FILE__ << " line:" << __LINE__ << "\nERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	return true;
}

void Shader::Use() const
{
	glUseProgram(ID);
}


void Shader::SetFloat(const std::string& name, float value) const
{
	Use();
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetVec2(const std::string& name, float value, float value2) const
{
	Use();
	glUniform2f(glGetUniformLocation(ID, name.c_str()), value, value2);
}


void Shader::SetVec3(const std::string& name, float value, float value2, float value3) const
{
	Use();
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value, value2, value3);
}

void Shader::SetVec4(const std::string& name, float value, float value2, float value3, float value4) const
{
	Use();
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value, value2, value3, value4);
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