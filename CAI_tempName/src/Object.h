#pragma once
//所有UI的基类

class Object 
{
public:
	Object() noexcept :invalid(false),value(nullptr),valueSize(0) { name = "Object"; }
	virtual ~Object() noexcept {
		if (value != nullptr)
			delete[] value;
	}
	Object(void* value,int size)noexcept:invalid(false) {
		this->value = new char[size];
		memcpy(this->value, value, size);
		valueSize = size;
	}
	Object(const Object& other) noexcept {
		*this = other;
	}
public:
	void setInvalid(bool isInvalid) { invalid = isInvalid; }
public:
	Object& operator=(const Object& other) { 
		invalid = other.invalid;
		if (!valueSize)
			return *this;
		value = new char[other.valueSize];
		memcpy(value, other.value, other.valueSize);
		valueSize = other.valueSize;
		return *this;
	}

public:
	bool isInvalid() const{ return invalid; }
	void setValue(void* arg,int size) {
		value = new char[size];
		memcpy(value, arg, size);
		valueSize = size;
	}
protected:
	bool invalid;
	std::string name;
	void* value;
	int valueSize;
};

