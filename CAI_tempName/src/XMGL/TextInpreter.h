#pragma once
#include<XMGLInterpreter/XMGLIntertpret.h>
class TextInpreter
{
public:
	void Init();
private:
	std::shared_ptr<XMGL::XMLInterpreter> xmglInpreter;
};

