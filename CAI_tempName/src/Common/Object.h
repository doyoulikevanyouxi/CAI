#pragma once
//所有UI的基类

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
protected:
	bool invalid;
	std::string name;
};

