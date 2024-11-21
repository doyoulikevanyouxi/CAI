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
	inline Size& ClipSize() const noexcept { return *clipSize; }
	inline Size& ContentSize() const noexcept { return *contentSize; }
	inline Draw::Brush& AreaBrush() const noexcept { return *areaBrush; }
	inline unsigned int VertexSize() const noexcept { return vertexSize; }
	inline unsigned int IndexSize() const noexcept { return indexSize; }
	void SetBorderSize(float value) noexcept;
	float* VertexData() const noexcept;
	void InitData();
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
	bool needClip;
private:
	friend class PaintDevice;
	friend class UIElement;
	friend class Control;
	//���������С
	Size* areaSize;
	//�߿��С
	float borderSize;
	//��ȥ�߿�����ݴ�С---�����ӿؼ����ڴ������ڻ���
	Size* contentSize;
	//�ü��ռ�---ֻ���Ƹ���������ݣ���������������ݽ����ᴦ��
	Size* clipSize;
	//����������ɫˢ
	Draw::Brush* areaBrush;
	Draw::Brush* borderBrush;
	//���ƶ�������
	float* vertexData;
	//����������
	float* vertexColorData;
	//�߿򶥵�����
	float* borderVertexData;
	//�߿򶥵���ɫ����
	float* borderVertexColorData;
	//������������
	float* textureIndexData;
	//������������
	unsigned int* vertexIndexData;
	//�߿�Ļ�������--ʵ���ϱ߿�Ļ��������ǿؼ�����Size�����������ģ�������������������Ļ���
	//�߿�Ļ��ƿ��������ؼ���Ӱ�Ļ���---��Ҫע�����������������Ϊ����ģ���������ᵼ������Ҳ�ܹ�������ӰЧ���������������Ҳ����Ӱ��ô��Ҫ���⴦��������Ⱦ���

	//�������ݸ���
	unsigned int vertexSize;
	//�������ݸ���
	unsigned int indexSize;
	//content������ID
	unsigned int texture;
	//�߿������ID
	unsigned int textureBorder;
};
