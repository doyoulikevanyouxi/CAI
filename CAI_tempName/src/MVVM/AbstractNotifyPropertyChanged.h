#pragma once
#include "Events/Events.h"
#include "UI/RenderEngine.h"
#include<map>
class AbstractNotifyPropertyChanged
{
protected:
	virtual void OnPropertyChanged(const char* propertyName) = 0;
	void PropertyChanged(void* dataContext, CAITF::PropertyChangedEvent* pEvent) {
		//pEvent->newValue = strToMap[pEvent->propertyName];
		pEvent->source = this;
		//pEvent->target = this;
		CAIEngine.EventReDistribute(*pEvent);
	}
private:
	//����
	std::map<std::pair<std::string,void*>, std::pair<std::string, void*>> bindMap;	 //���� + ��ַ       ����+��ַ
};

