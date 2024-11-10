#pragma once
class AbstractExpression {
protected:
	virtual void Interpret(const char* str) = 0;
};