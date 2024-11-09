#pragma once
#include"Mathmatics/Math.hpp"
class Shader
{
	class string;
public:
	Shader();
	Shader(const std::string& shaFilePath);
	~Shader();
public:
	bool load(const std::string& shaFilePath);
	void use() const;
	void setVec3(const std::string& name, float value,float value2,float value3) const;
	void setVec4(const std::string& name, float value,float value2,float value3,float value4) const;
	void setMat4(const std::string& name, const Math::TransMatrix& mat) const;
	void setMat4(const std::string& name, const float* mat) const;
	float* getMat4(const std::string& name);
private:
	unsigned int vertexShader;
	unsigned int fragmentShader;
	std::string vertexshaderStr;
	std::string fragmentshaderStr;
	unsigned int ID;
	bool isLoad;
};

