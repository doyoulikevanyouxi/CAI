#pragma once
#include "Object.h"
#include<vector>
class UIElement;
//namespace std {
//	template<typename>
//	class vector {
//	public:
//		class iterator;
//	};
//}

class UIElementCollection final : public Object
{
public:
	UIElementCollection() noexcept;
	~UIElementCollection() noexcept;
public:
	size_t Size() const noexcept;
public:
	using iterator = std::vector<UIElement*>::iterator;
	iterator begin();
	iterator end();
public:
	void addChild(UIElement* child);
private:
	std::vector<UIElement*>* childs;
	UIElement** m_data;
	size_t size;
};

//template<typename _Ty>
//class Collection :public Object{
//public:
//	Collection() noexcept {}
//	~Collection() noexcept {}
//public:
//	using iterator = std::vector<_Ty>::iterator;
//	iterator begin() { return childs.begin(); }
//	iterator end() { return childs.end(); }
//private:
//	std::vector<_Ty> childs;
//	size_t size;
//};

