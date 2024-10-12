#pragma once
#include "Object.h"
#include<vector>
class UIElement;


template<typename _Ty>
class Collection :public Object {
public:
	Collection() noexcept { name = "collection"; }
	~Collection() noexcept {}
public:
	void addChild(const _Ty& child) { childs.emplace_back(child); }
	size_t Size() noexcept { return childs.size(); }
	auto begin() { return childs.begin(); }
	auto end() { return childs.end(); }
public:
	_Ty& operator[](size_t index) { return childs[index]; }
private:
	std::vector<_Ty> childs;
};

using UIElementCollection = Collection<UIElement*>;
