#pragma once
#include "Object.h"
class Size;
namespace Draw {
	class Brush;
}
/// <summary>
/// ������һ���ؼ������л�������
/// </summary>
class VisualData final : public Object {
public:
	VisualData() noexcept;
	VisualData(const VisualData& other) noexcept;
	//VisualData(VisualData&& other) noexcept;
	~VisualData()	noexcept;
public:
	inline Size& AreaSize() const noexcept { return *areaSize; }
	inline Size& ContentSize() const noexcept { return *contentSize; }
	inline Draw::Brush& AreaBrush() const noexcept { return *areaBrush; }
	inline unsigned int VertexSize() const noexcept { return vertexSize; }
	inline unsigned int IndexSize() const noexcept { return indexSize; }
	void setBorderSize(float value) noexcept;
	float* VertexData() const noexcept;
	void initData();
	unsigned int* VertexIndexData() const noexcept;

public:
	VisualData& operator=(const VisualData& other) noexcept;
	
	//���������������Դ̫�鷳�ˣ���ʱ��д�ƶ���ֵ
	/*VisualData& operator=(VisualData&& other) noexcept {
		areaSize = other.areaSize;
		areaBrush = other.areaBrush;
		vertexData = other.vertexData;
		vertexStride = other.vertexStride;
		colorStride = other.colorStride;
		vertexSize = other.vertexSize;
		indexSize = other.indexSize;
		invalid = other.invalid;
		other.areaSize = nullptr;
		other.areaBrush = nullptr;
		other.vertexData = nullptr;
		return *this;
	}*/
public:
	bool isDataHasBeenPushToGpu;
	bool hasBorder;
private:
	friend class PaintDevice;
	//���������С
	mutable Size* areaSize;
	//�߿��С
	mutable float borderSize;
	//��ȥ�߿�����ݴ�С---�����ӿؼ����ڴ������ڻ���
	mutable Size* contentSize;
	//����������ɫˢ
	mutable Draw::Brush* areaBrush;
	mutable Draw::Brush* borderBrush;
	//���ƶ�������
	mutable float* vertexData;
	mutable float* borderData;
	//������������
	mutable unsigned int* vertexIndexData;

	//�������ݸ���
	mutable unsigned int vertexSize;
	//�������ݸ���
	mutable unsigned int indexSize;
	//����ID
	mutable unsigned int texture;
};
