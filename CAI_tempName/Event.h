#pragma once
#include "Object.h"
//using event = void (*)(GLFWwindow* window, double xoffset, double yoffset);
//�¼�ϵͳ�Ǻܺÿ����ġ�ԭ������һ�����ڵ���Ⱦ�ǵ��̵߳ģ����������ݾ�������
//��Ҫ��ȡ�Ĺ̶�״̬�У��������ݣ�������ݡ�����ֻ�а������⣬�������λ�úͰ�������������Ҫ����
//��ô�����ַ�ʽ��һ����GLFW���¼��������Ļ�����ע��ص���Ȼ�������Լ����¼������¼������
//��һ������ѯ�ķ�ʽ
class EventArgs {
public:
	Object* who;
	Object* value;
};
enum EventType
{
	Tunnel,
	Bubble
};
class Event {
public:
	EventArgs args;
};