#pragma once
#include"Mathmatics/Math.hpp"
class string;
/// <summary>
/// 着色器类，该类用于生成着色器程序
/// 
/// </summary>
class Shader
{
public:
	//构造函数，必须提供前两个参数：顶点着色器文件和片段着色器文件
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath);
	~Shader();
public:
	//编译着色器
	bool ComplieShader();
	/// <summary>
	/// 以下根据opengl设置glsl的uniform数据
	/// 暂时未添加uniform块数据的设置
	/// </summary>
	
	void SetFloat(const std::string& name, float value) const;
	void SetVec2(const std::string& name, float value, float value2) const;
	void SetVec3(const std::string& name, float value, float value2, float value3) const;
	void SetVec4(const std::string& name, float value, float value2, float value3, float value4) const;
	void SetMat4(const std::string& name, const Math::TransMatrix& mat) const;
	void SetMat4(const std::string& name, const float* mat) const;
public:
	//着色器程序ID
	unsigned int ID;
private:
	//顶点着色器文件路径
	std::string vertexShaderPath;
	//片段着色器文件路径
	std::string fragmentShaderPath;
	//几何着色器文件路径
	std::string geometryShaderPath;
	//顶点着色器文本
	std::string vertexStr;
	//片段着色器文本
	std::string fragmentStr;
	//几何做瑟琪文本
	std::string geometryStr;
private:
	//加载文件
	bool Load(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath);
	//加载着色器文本
	void LoadShadder(const std::string& filePath, std::string& shaderStr);
	//编译着色器程序
	inline bool CheckComplieError(const unsigned int& shader);
public:
	//使用着色器程序
	void Use() const;
};


