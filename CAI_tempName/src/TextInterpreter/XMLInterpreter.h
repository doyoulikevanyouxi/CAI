#pragma once
#include "AbstractExpression.h"
class XMLTerimalExpression final : public AbstractExpression {
public:
	const char ex = '>';
	XMLTerimalExpression() = default;
	void Interpret(const char* str) override;
};

class XMLNonterimalExpression final : public AbstractExpression {
	friend class XMLInterpreter;
public:
	XMLNonterimalExpression() = default;
protected:
	void Interpret(const char* str) override;
	std::string str;
private:
	XMLTerimalExpression texpr;
	const char ex = '<';
};


//XML�ı�������
class XMLInterpreter
{
public:
	XMLInterpreter() noexcept =default;
	XMLInterpreter(const std::string& path) noexcept;
	~XMLInterpreter() noexcept;
public:
	//�����ļ�
	void Load(const std::string& path);
	//�����ַ���
	void Interpret();
public:
	//����״̬---ƥ��ģʽ״̬
	static bool status;
private:
	XMLNonterimalExpression nexpr;
	std::string str;
	std::ifstream file;

};

