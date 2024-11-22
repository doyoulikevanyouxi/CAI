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
	//����ؼ����ɼ��ͷ���
	/*if (element) {
		return;
	}*/
	//��ǰ�±�ָ�����β����˵����ǰ����������ָ��û������
	//��ô��ʱֻ�����������겻�����
	if (mouseOverElemntIndex == eles.size()) {
		if (size.PointIn(e.X(), e.Y())) {
			eles.emplace_back(element);
			++mouseOverElemntIndex;
			//��������
			for (auto& child : element->style->visualTree) {
				MouseMouseHandle(e, child, mouseOverElemntIndex);
				if (e.handled)
					break;
			}
			//����MouseEnter�¼�
			MouseEnterEvent e;
			element->OnMouseEnter(e);
			e.handled = true;
			return;
		}
		//���ھ�ֱ��return;
		return;
	}
	//����ǿ�����β
	//�����ͬ
	if (eles[mouseOverElemntIndex] == element) {
		//�������
		if (size.PointIn(e.X(), e.Y())) {
			//����premouseOver�¼�
			PreMouseOverEvent ev(e.X(),e.Y());
			++mouseOverElemntIndex;
			//���´���
			for (auto& child : element->style->visualTree) {
				MouseMouseHandle(e, child, mouseOverElemntIndex);
				if (e.handled)
					break;
			}
			//����mouseOver�¼�
			MouseOverEvent ex(e.X(), e.Y());
			element->OnMouseOver(ex);
			e.handled = true;
			return;
		}
		//���δ����
		size_t index = eles.size() - 1;
		while (index >= mouseOverElemntIndex) {
			MouseLeaveEvent exc;
			element->OnMouseLeave(exc);
			eles.pop_back();
			--index;
		}
		//�������ͽ����˿ؼ�����β��
		return;
	}

	//�������ͬ
		//�������
		if (size.PointIn(e.X(), e.Y())) {
			size_t index = eles.size() - 1;
			while (index >= mouseOverElemntIndex) {
				//����mouseleave
				MouseLeaveEvent exc;
				eles[index]->OnMouseLeave(exc);
				eles.pop_back();
				--index;
			}
			eles.emplace_back(element);
			//��ʱҲ�ǿؼ�����β��
			++mouseOverElemntIndex;
			//���´���
			for (auto& child : element->style->visualTree) {
				MouseMouseHandle(e, child, mouseOverElemntIndex);
				if (e.handled)
					break;
			}
			//����mouseenter�¼�
			MouseEnterEvent ev;
			element->OnMouseEnter(ev);
			e.handled = true;
			return;
		}
		//���û����
		return;
}
ApplicationControl::ApplicationControl() : currentElement(nullptr)
{
	//������ָ�������ǿյ�
	//������ָ������ǿ�
	//��Ҫ��ջ����Ԫ�رȽ�
}

