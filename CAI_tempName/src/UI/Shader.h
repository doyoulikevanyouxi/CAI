#pragma once
#include"Mathmatics/Math.hpp"
class string;
/// <summary>
/// ��ɫ���࣬��������������ɫ������
/// 
/// </summary>
class Shader
{
public:
	//���캯���������ṩǰ����������������ɫ���ļ���Ƭ����ɫ���ļ�
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath);
	~Shader();
public:
	//������ɫ��
	bool ComplieShader();
	/// <summary>
	/// ���¸���opengl����glsl��uniform����
	/// ��ʱδ���uniform�����ݵ�����
	/// </summary>
	
	void SetFloat(const std::string& name, float value) const;
	void SetVec2(const std::string& name, float value, float value2) const;
	void SetVec3(const std::string& name, float value, float value2, float value3) const;
	void SetVec4(const std::string& name, float value, float value2, float value3, float value4) const;
	void SetMat4(const std::string& name, const Math::TransMatrix& mat) const;
	void SetMat4(const std::string& name, const float* mat) const;
public:
	//��ɫ������ID
	unsigned int ID;
private:
	//������ɫ���ļ�·��
	std::string vertexShaderPath;
	//Ƭ����ɫ���ļ�·��
	std::string fragmentShaderPath;
	//������ɫ���ļ�·��
	std::string geometryShaderPath;
	//������ɫ���ı�
	std::string vertexStr;
	//Ƭ����ɫ���ı�
	std::string fragmentStr;
	//������ɪ���ı�
	std::string geometryStr;
private:
	//�����ļ�
	bool Load(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& geometryShaderPath);
	//������ɫ���ı�
	void LoadShadder(const std::string& filePath, std::string& shaderStr);
	//������ɫ������
	inline bool CheckComplieError(const unsigned int& shader);
public:
	//ʹ����ɫ������
	void Use() const;
};


