#include "caipch.h"
#include "XMLInterpreter.h"
bool XMLInterpreter::status = false;
void XMLTerimalExpression::Interpret(const char* str)
{
	XMLInterpreter::status = false;
}

void XMLNonterimalExpression::Interpret(const char* str)
{
	const char* ch = str;
	for (int i = 0; *(ch+i)!='\0'; ++i) {
		if (*(ch + i) == ex) {
			if (XMLInterpreter::status) {
				std::cout << "invalid expression" << std::endl;
				break;
			}
			XMLInterpreter::status = true;
			XMLNonterimalExpression tmp;
			tmp.Interpret((ch + i + 1));
			break;
		}
		if (*(ch + i) == '>') {
			texpr.Interpret(ch);

		}
		else {
			this->str += *(ch + i);
		}
	}
	std::cout << this->str << std::endl;
}

XMLInterpreter::XMLInterpreter(const std::string& path) noexcept
{
	Load(path);
}

XMLInterpreter::~XMLInterpreter() noexcept
{
	if (file.is_open())
		file.close();
}

void XMLInterpreter::Interpret()
{
	nexpr.Interpret(str.c_str());
}

void XMLInterpreter::Load(const std::string& path)
{
	file.open(path);
	if (!file.is_open()) {
		std::cout << "No such file named:" << path << std::endl;
		return;
	}
	std::string tmp;
	while (std::getline(file, tmp)) {
		str += tmp + "\n";
	}
	file.close();
}
