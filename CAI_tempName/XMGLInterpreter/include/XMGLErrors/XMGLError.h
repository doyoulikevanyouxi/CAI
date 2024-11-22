#pragma once
#include "XMLGAbstractError.h"

namespace XMGL {
	/// <summary>
/// 无效字符串
/// </summary>
class XMGLInvalidString :public AbstractError
{
public:  
	XMGLInvalidString(unsigned int line = 0, unsigned int column = 0);
	XMGLInvalidString(const char* invalidStr = nullptr, unsigned int line = 0,unsigned int column = 0);
	// 通过 AbstractError 继承
	void ErrorMessage() const override;
};

/// <summary>
/// 意外的字符
/// </summary>
class XMGLUnexpectedSymbol : public AbstractError {
public:
	XMGLUnexpectedSymbol(unsigned int line = 0, unsigned int column = 0);
	XMGLUnexpectedSymbol(const char symbol, unsigned int line = 0, unsigned int column = 0);
	// 通过 AbstractError 继承
	void ErrorMessage() const override;
private:
	char symbol;
};

class XMGLError : public AbstractError {
public:
	XMGLError(const char* str,unsigned int line = 0, unsigned int column = 0);
	// 通过 AbstractError 继承
	void ErrorMessage() const override;
private:
};
}

