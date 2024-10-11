//该文件定义了控件的属性字段
//这些类规定了控件属性应该属于哪种类型并且，会注册到一个系统中进行管理

#pragma once
#include "Object.h"
#include<string>
class Property : public Object
{
};

template<typename _Ty>
class DependencyProperty : public Property {
public:
	DependencyProperty() = delete;
	DependencyProperty(const std::string& name) noexcept:name(name) {}
public:
	void set(const _Ty& value) noexcept { this->value = value; }
	_Ty& get() const noexcept{ return value; }
public:
	DependencyProperty<_Ty>& operator=(const _Ty& value) { this->value = value; return *this; }
private:
	mutable _Ty value;
	std::string name;
};

template<typename _Ty>
class AttachedProperty : public Property {
public:
	AttachedProperty() = delete;
	AttachedProperty(const std::string& name) noexcept :name(name) {}
public:
	_Ty& Value() { return value; }
private:
	mutable _Ty value;
	std::string name;
};
