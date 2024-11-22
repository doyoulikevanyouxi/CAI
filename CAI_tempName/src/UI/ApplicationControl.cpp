#include "caipch.h"
#include "ApplicationControl.h"
#include "UIElement.h"
#include "Datas/ControlStyle.h"
#include "Datas/Coordinate.h"
ApplicationControl ApplicationControl::app;

void ApplicationControl::OnMouseMove(MouseMoveEvent& e, UIElement* win)
{
	MouseMouseHandle(e, win->style->visualTree[0], 0);
}

void ApplicationControl::MouseMouseHandle(MouseMoveEvent& e, UIElement*& element, size_t mouseOverElemntIndex)
{
	const Size& size = element->style->vData.GlobalAreaSize();
	//如果控件不可见就返回
	/*if (element) {
		return;
	}*/
	//当前下标指向队列尾部，说明，前面的所有鼠标指向都没有问题
	//那么此时只有鼠标进入或鼠标不在这里。
	if (mouseOverElemntIndex == eles.size()) {
		if (size.PointIn(e.X(), e.Y())) {
			eles.emplace_back(element);
			++mouseOverElemntIndex;
			//继续向下
			for (auto& child : element->style->visualTree) {
				MouseMouseHandle(e, child, mouseOverElemntIndex);
				if (e.handled)
					break;
			}
			//发出MouseEnter事件
			MouseEnterEvent e;
			element->OnMouseEnter(e);
			e.handled = true;
			return;
		}
		//不在就直接return;
		return;
	}
	//如果非控制链尾
	//如果相同
	if (eles[mouseOverElemntIndex] == element) {
		//如果进入
		if (size.PointIn(e.X(), e.Y())) {
			//发出premouseOver事件
			PreMouseOverEvent ev(e.X(),e.Y());
			++mouseOverElemntIndex;
			//向下传递
			for (auto& child : element->style->visualTree) {
				MouseMouseHandle(e, child, mouseOverElemntIndex);
				if (e.handled)
					break;
			}
			//发出mouseOver事件
			MouseOverEvent ex(e.X(), e.Y());
			element->OnMouseOver(ex);
			e.handled = true;
			return;
		}
		//如果未进入
		size_t index = eles.size() - 1;
		while (index >= mouseOverElemntIndex) {
			MouseLeaveEvent exc;
			element->OnMouseLeave(exc);
			eles.pop_back();
			--index;
		}
		//处理完后就进入了控件链的尾部
		return;
	}

	//如果不相同
		//如果进入
		if (size.PointIn(e.X(), e.Y())) {
			size_t index = eles.size() - 1;
			while (index >= mouseOverElemntIndex) {
				//发出mouseleave
				MouseLeaveEvent exc;
				eles[index]->OnMouseLeave(exc);
				eles.pop_back();
				--index;
			}
			eles.emplace_back(element);
			//此时也是控件链的尾部
			++mouseOverElemntIndex;
			//向下传递
			for (auto& child : element->style->visualTree) {
				MouseMouseHandle(e, child, mouseOverElemntIndex);
				if (e.handled)
					break;
			}
			//发出mouseenter事件
			MouseEnterEvent ev;
			element->OnMouseEnter(ev);
			e.handled = true;
			return;
		}
		//如果没进入
		return;
}
ApplicationControl::ApplicationControl() : currentElement(nullptr)
{
	//如果鼠标指向数组是空的
	//如果鼠标指向数组非空
	//需要按栈进行元素比较
}

