#include "caipch.h"
#include "Visual.h"
#include "Application.h"
#include "RenderEngine.h"
#include "PaintDeivces/PaintDevice.h"
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
	//裁剪测试，由于float精度问题，可能存在裁剪过后存在间隙
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
	vData.SetBorderSize(value);
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
	vData.SetAreaBrush(color);
}

void Visual::SetBackground(const uint32_t color)
{
	background.set(Draw::Brush(color));
	vData.SetAreaBrush(color);
}

void Visual::SetBorderBrush(const Draw::Brush& color)
{
	vData.SetBorderBursh(color);
}

void Visual::SetVisible(const bool visible)
{
	this->visible.set(visible);
	vData.Visible() = visible;
}

void Visual::SetRadius(const float& value)
{
	radius.set(value);
	vData.SetRadius(value, value, value, value);
}

void Visual::CheckSize(const Size& size) noexcept
{
	Aeasure(Measure(size));
	visualTree->SortByZindex();
}

Size Visual::Measure(const Size& size) noexcept
{
	if (parent != nullptr) {
		if (!parent->vData.Visible())
			vData.Visible() = false;
	}
	//设置分辨率
	vData.SetResolution(size.ResolutionWidth(), size.ResolutionHeight());
	//设置裁减区域
	Point pt(size.X(), size.Y());
	Point::TranslatTo(pt, size.ModelMatrix());
	Point::Reverse(pt, size.ResolutionHeight());
	Point::SetToLeftBottom(pt,size.Height());
	vData.SetClipSize(Size(pt.X(),pt.Y(), size.Z(), size.Width(), size.Height()));
	
	//未设置宽度值时，采用传递过来的大小
	if (width.IsInvalid()) {
		SetActualWidth(size.Width());
	}
	if (height.IsInvalid()) {
		SetActualHeight(size.Height());
	}
	vData.SetWH(actualWidth, actualHeight);
	
	//接着将根据给定的父变换矩阵来设置控件自身的变换矩阵
	Math::mat4 tMatrix = {
						1,0,0,0,
						0,1,0,0,
						0,0,1,0,
						(float)size.X(),(float)size.Y(),0,1
	};
	//如果z值未设置，那么将继承上个z值并+1
	float z = 0;
	if (!zIndex.IsInvalid())
		z = zIndex.get();
	else
		z = size.Z() + 1;
	vData.SetPoint(vData.AreaSize().X(), vData.AreaSize().Y(), z);
	vData.SetModel(size.ModelMatrix() * tMatrix);
	vData.SetProjection(size.ProjectionMatrix());

	if (zmax < z)
		zmax = z;
	//初始化控件顶点数据
	pDevice->UpdateData(vData.VertexData(),vData.SizeData(),vData.VertexColorData(),vData.RadiusData(),vData.BorderSizeData(),vData.BorderColorData());
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
