#pragma once
#include<string>
namespace XMGL {
	class AbstractError {
	public:
		AbstractError(unsigned int code = 0, unsigned int line = 0, unsigned int column = 0) :errorCode(code), line(line), column(column) {}
	public:
		inline unsigned int GetErrorCode() const noexcept { return errorCode; }
		inline unsigned int GetLine() const noexcept { return line; }
		inline unsigned int GetColumn() const noexcept { return column; }
		virtual void ErrorMessage() const = 0;
	protected:
		unsigned int errorCode;
		unsigned int line;
		unsigned int column;
		std::string message;
	};
}

