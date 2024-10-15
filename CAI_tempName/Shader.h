#pragma once
#include<string>
#include"Math.hpp"
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
	void setMat4(const std::string& name, const Math::TransMatrix& mat) const;
	void setMat4(const std::string& name, const float* mat) const;
	float* getMat4(const std::string& name);
private:
#if  _HAS_CXX17
	[[maybe_unused]]
#endif //  _HAS_CXX17
private:
	unsigned int vertexShader;
	unsigned int fragmentShader;
	std::string vertexshaderStr;
	std::string fragmentshaderStr;
	unsigned int ID;
	bool isLoad;
};

