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


//XML文本解释器
class XMLInterpreter
{
public:
	XMLInterpreter() noexcept =default;
	XMLInterpreter(const std::string& path) noexcept;
	~XMLInterpreter() noexcept;
public:
	//加载文件
	void Load(const std::string& path);
	//解释字符串
	void Interpret();
public:
	//解释状态---匹配模式状态
	static bool status;
private:
	XMLNonterimalExpression nexpr;
	std::string str;
	std::ifstream file;

};

