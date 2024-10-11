#pragma once
#include "Object.h"
#include <vector>
class PropertyChangedArgs {
public:
	std::string name;
	Object& newValue;
	Object& oldValue;
};
enum BindModel {
	Single,
	TowWay
};
class VirtualPropertyChanged {
public:
	void virtual onPropertyChanged(PropertyChangedArgs& arg) = 0;
	//���󶨵�������������Ҫһ��
	template<typename _T>
	static void bind(_T& source, _T& target, BindModel mod = TowWay) {
		
	}
public:
	
protected:
	std::vector<Object*> who;
};