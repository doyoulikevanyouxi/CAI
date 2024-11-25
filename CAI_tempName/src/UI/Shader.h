#pragma once
#include"Mathmatics/Math.hpp"
class string;
class Shader
{
public:
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath);
	~Shader();
public:
	bool ComplieShader();
	void SetVec3(const std::string& name, float value, float value2, float value3) const;
	void SetVec4(const std::string& name, float value, float value2, float value3, float value4) const;
	void SetMat4(const std::string& name, const Math::TransMatrix& mat) const;
	void SetMat4(const std::string& name, const float* mat) const;
public:
	unsigned int ID;
private:
	std::string vertexShaderPath;
	std::string fragmentShaderPath;
	std::string geometryShaderPath;
	std::string vertexStr;
	std::string fragmentStr;
	std::string geometryStr;
private:
	bool Load(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath);
	void LoadShadder(const std::string& filePath, std::string& shaderStr);
	inline bool CheckComplieError(const unsigned int& shader);
public:
	void Use() const;
};


