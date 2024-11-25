#pragma once
//所有UI的基类
#include<string>
class Object 
{
public:
	Object() noexcept :invalid(false){ name = "Object"; }
	Object(const Object& other) noexcept {
		*this = other;
	}
public:
	void SetInvalid(bool isInvalid) { invalid = isInvalid; }
public:
	Object& operator=(const Object& other) { 
		invalid = other.invalid;
		name = other.name;
		return *this;
	}

public:
	bool IsInvalid() const{ return invalid; }
public:
	std::string name;
	bool invalid;
};

