#pragma once
#include "Decoration.h"
#include "Draw.h"
/// <summary>
/// Border�ؼ�����ʾ�����ӿؼ��ı߿�
/// </summary>
class Border : public Decoration
{
	using Decoration::Decoration;
//public:
//	Border(UIElement* attachedto) noexcept:Decoration(attachedto) {}
//	~Border()noexcept {}
private:
	friend class Control;
	float size;
	Draw::Color color;
};

