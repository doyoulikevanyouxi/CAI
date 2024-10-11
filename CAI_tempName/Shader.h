#pragma once
#include<string>
class Shader
{
	class string;
public:
	Shader();
	Shader(const std::string& shaFilePath);
	~Shader();
public:
	bool load(const std::string& shaFilePath);
	void use();
private:
#if  _HAS_CXX17
	[[maybe_unused]]
#endif //  _HAS_CXX17
	inline bool compileShader();
private:
	unsigned int vertexShader;
	unsigned int fragmentShader;
	std::string vertexshaderStr;
	std::string fragmentshaderStr;
	unsigned int ID;
	bool isLoad;
};

