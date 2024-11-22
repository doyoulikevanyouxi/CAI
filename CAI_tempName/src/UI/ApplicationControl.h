#pragma once
#include "Events/Events.h"
#include <stack>
class UIElement;
/// <summary>
/// �����������
/// ���������ƶ�
/// </summary>
class ApplicationControl
{
public:
	static ApplicationControl app;
public:
	void OnMouseMove(MouseMoveEvent& e, UIElement* win);
private:
	void MouseMouseHandle(MouseMoveEvent& e,UIElement*& element,size_t mousOverElemntIndex);
	ApplicationControl();
private:
	UIElement* currentElement;
	//����������Ŀؼ���ÿ����һ���ؼ�������ѹ��һ��
	//�жϽ����׼�ǣ����ؼ��϶����룬��Ҫ���ӿؼ�������ӿؼ������غ���һ����ʱ����Ҫ��zֵ����һ���ؼ���ʼ������Ϣ
	//���zֵ���Ľ����ˣ���ô�����ľ�û�н���
	//�������غ�ʱ�����������������Ƚ�������zֵ�ؼ�����ô�Ͳ�����
	std::deque<UIElement*> eles;
};

