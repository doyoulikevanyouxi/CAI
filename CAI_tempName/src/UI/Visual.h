#pragma once
#include "Element.h"
/// <summary>
/// Visual 是所有图形的渲染层次，暂时不完成，涉及到可视化树的事件传递问题
/// 本身可视化不具备事件，因此事件不应该传递到只管渲染的此处
/// </summary>
class Visual : public Element
{
};

