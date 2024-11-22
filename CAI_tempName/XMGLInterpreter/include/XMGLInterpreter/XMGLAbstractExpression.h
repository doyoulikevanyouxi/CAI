#pragma once

namespace XMGL {
#define bit(x) 1<<x
	class AbstractError;
	class Tag;
	class XMLAbstractExpression {
	public:
		virtual bool Interpret(const char*& str, Tag& tag) = 0;
	protected:
		virtual void RaiseError(const AbstractError& error) = 0;
	};
}
