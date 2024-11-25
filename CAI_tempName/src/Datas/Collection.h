#pragma once
template<typename _Ty>
class Collection  {
public:
	Collection() noexcept = default;
	Collection(const Collection& other) {
		*this = other;
	}
	~Collection() noexcept = default;
public:
	void AddChild(const _Ty& child) { childs.emplace_back(child); }
	size_t Size() noexcept { return childs.size(); }
	auto begin() { return childs.begin(); }
	auto end() { return childs.end(); }
	_Ty& last() { return childs.back(); }
	bool empty() { return childs.empty(); }
public:
	_Ty& operator[](size_t index) { return childs[index]; }
	Collection& operator=(const Collection& other) {
		childs = other.childs;
		return *this;
	}
protected:
	std::vector<_Ty> childs;
};
