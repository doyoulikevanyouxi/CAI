#pragma once
#include "Events/Events.h"
#include "UI/RenderEngine.h"
#include<map>

//class Binding {
//public:
//	enum Mode {
//		OneWay,
//		TwoWay,
//		Defualt
//	};
//public:
//	void* source;
//	std::string path;
//	Mode mod = TwoWay;
//	void* target;
//	std::string targetPath;
//};
//
//
//
//class MVVM {
//private:
//	MVVM() {}
//public:
//	static void RigistBinding(Binding& binding);
//};
//
//class NotifyPropertyChanged {
//
//public:
//	void SetBinding(std::string propertyName, Binding& binding) {
//		binding.target = this;
//		binding.targetPath = propertyName;
//	}
//	void PropertyChanged(const char* propertyName) {
//
//	}
//};