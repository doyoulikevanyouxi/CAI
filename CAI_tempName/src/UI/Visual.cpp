#include "caipch.h"
#include "Visual.h"
#include "Application.h"
#include "RenderEngine.h"
#include "PaintDevice.h"
#include "Draw.h"
#include "Datas/VisualData.h"
#include "Datas/VisualCollection.h"
float zmax = 1;

Visual::Visual(Visual* parent) : parent(parent),pDevice(nullptr), visualTree(new VisualCollection())
{
}

Visual::Visual(const Visual& other)
{
	*this = other;
}

Visual::~Visual()
{
	delete visualTree;
}

bool Visual::Init()
{
	pDevice = Application::app.renderEngine->GetPaintDevice();
	for (auto& visual : *visualTree) {
		visual->Init();
	}
	return true;
}

void Visual::Render()
{
	pDevice->Draw(vData);
	//�ü����ԣ�����float�������⣬���ܴ��ڲü�������ڼ�϶
	for (auto& visual : *visualTree) {
		visual->Render();
	}
}

void Visual::SetVisualParent(Visual* parent)
{
	this->parent = parent;
}

void Visual::AddVisualChild(Visual* child)
{
	visualTree->AddChild(child);
}




void Visual::operator=(const Visual& other)
{
	vData = other.vData;
	pDevice = other.pDevice;
	parent = other.parent;
	*visualTree = *(other.visualTree);

	width = other.width.get();
	height = other.height.get();
	maxWidth = other.maxWidth.get();
	maxHeight = other.maxHeight.get();
	minWidth = other.minWidth.get();
	minHeight = other.minHeight.get();
	actualWidth = other.actualWidth;
	actualHeight = other.actualHeight;
	background = other.background.get();
}

void Visual::SetHeight(float value)
{
	height.set(value);
	SetActualHeight(value);
	validHeight = true;
}

void Visual::SetWidth(float value)
{
	width.set(value);
	SetActualWidth(value);
	validWidth = true;
}

void Visual::SetZindex(float value)
{
	zIndex.set(value);
}

void Visual::SetBorderSize(float value)
{
	borderSize.set(value);
}

void Visual::SetWidthAndHeight(float width, float height)
{
	SetWidth(width);
	SetHeight(height);
}

void Visual::SetMinHeight(float value)
{
	minHeight.set(value);
	if (actualHeight < value)
		actualHeight = value;
	validHeight = true;
}

void Visual::SetMinWidth(float value)
{
	minWidth.set(value);
	if (actualWidth < value) {
		actualWidth = value;
	}
	validWidth = true;
}

void Visual::SetMaxHeight(float value)
{
	maxHeight.set(value);
	if (actualHeight > value)
		actualHeight = value;
	validHeight = true;
}

void Visual::SetMaxWidth(float value)
{
	maxWidth.set(value);
	if (actualWidth > value)
		actualWidth = value;
	validWidth = true;
}

void Visual::SetBackground(const Draw::Brush& color)
{
	background.set(color);
	vData.AreaBrush() = color;
}

void Visual::SetBackground(const uint32_t color)
{
	background.set(Draw::Brush(color));
	vData.AreaBrush() = Draw::Brush(color);
}

void Visual::SetBorderBrush(const Draw::Brush& color)
{
	*(vData.borderBrush) = color;
}

void Visual::SetVisible(const bool visible)
{
	this->visible.set(visible);
	vData.visibale = visible;
}

void Visual::CheckSize(const Size& size) noexcept
{
	Aeasure(Measure(size));
	visualTree->SortByZindex();
}

Size Visual::Measure(const Size& size) noexcept
{
	if (parent != nullptr) {
		if (!parent->vData.visibale)
			vData.visibale = false;
	}
	vData.AreaSize().SetGlobalWidth(size.GlobalWidth());
	vData.AreaSize().SetGlobalHeight(size.GlobalHeight());
	Point tmp(size.X(), size.Y());
	tmp.Y() += size.Height();
	Point::TranslatTo(tmp, size.TransMatrix());
	Point::SetToLeftBottom(tmp, size.GlobalHeight());
	if (tmp.Y() < 0)
		tmp.Y() = 0;
	//���òü�����
	vData.clipSize->setX(tmp.X());
	vData.clipSize->setY(tmp.Y());
	vData.clipSize->SetWidth(size.Width());
	vData.clipSize->SetHeight(size.Height());
	//δ���ÿ��ֵʱ�����ô��ݹ����Ĵ�С
	if (width.IsInvalid()) {
		SetActualWidth(size.Width());
	}
	if (height.IsInvalid()) {
		SetActualHeight(size.Height());
	}
	vData.AreaSize().SetWidth(actualWidth);
	vData.AreaSize().SetHeight(actualHeight);
	//���Ž����ݸ����ĸ��任���������ÿؼ�����ı任����
	Math::SquareMatrix<4> tMatrix = {
									1,0,0,0,
									0,1,0,0,
									0,0,1,0,
									size.X(),size.Y(),0,1
	};
	//���zֵδ���ã���ô���̳��ϸ�zֵ��+1
	if (!zIndex.IsInvalid())
		vData.AreaSize().setZ(zIndex.get());
	else
		vData.AreaSize().setZ(size.Z() + 1);
	vData.AreaSize().TransMatrix() = size.TransMatrix() * tMatrix;
	if (zmax < vData.AreaSize().Z())
		zmax = vData.AreaSize().Z();
	//����б߿򣬾ͽ��߿����
	if (!borderSize.IsInvalid())
		vData.SetBorderSize(borderSize.get());
	//��ʼ���ؼ���������
	vData.InitData();
	pDevice->UpdateData(vData.vertexData, vData.vertexColorData,vData.vertexIndexData);
	return vData.ContentSize();
}

void Visual::Aeasure(const Size& size) noexcept
{
	for (auto& child : *visualTree) {
		child->CheckSize(size);
	}
}


inline void Visual::SetActualHeight(float value)
{
	actualHeight = value;
	if (!minHeight.IsInvalid()) {
		if (value < minHeight.get()) {
			actualHeight = minHeight.get();
		}
	}
	if (!maxHeight.IsInvalid()) {
		if (value > maxHeight.get()) {
			actualHeight = maxHeight.get();
		}
	}

}

inline void Visual::SetActualWidth(float value)
{
	actualWidth = value;
	if (!minWidth.IsInvalid()) {
		if (value < minWidth.get()) {
			actualWidth = minWidth.get();
		}
	}
	if (!maxWidth.IsInvalid()) {
		if (value > maxWidth.get()) {
			actualWidth = maxWidth.get();
		}
	}
}

Size& Visual::GetSize()
{
	return vData.AreaSize();
}
