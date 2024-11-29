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
	friend class Visual;
	friend class PaintDevice;
public:
	VisualData() noexcept;
	VisualData(const VisualData& other) noexcept;
	//VisualData(VisualData&& other) noexcept;
	~VisualData()	noexcept;
public:
	//����Ԫ�ص�size
	inline Size& AreaSize() const noexcept { return *areaSize; }
	//����Ԫ��������Ƶķ�Χsize
	inline Size& ClipSize() const noexcept { return *clipSize; }
	//����Ԫ�����ݵ�size
	inline Size& ContentSize() const noexcept { return *contentSize; }
	//��ʵ�Ƿֱ���
	inline Size& GlobalAreaSize() const noexcept { return *globalAreaSize; }
	//����Ԫ�صı�ˢ
	inline Draw::Brush& AreaBrush() const noexcept { return *areaBrush; }
	inline unsigned int VertexSize() const noexcept { return vertexSize; }
	inline unsigned int IndexSize() const noexcept { return indexSize; }
	//���ñ߿��С
	void SetBorderSize(double value) noexcept;
	double* VertexData() const noexcept;
	//��ʼ����Ⱦ����
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
	//�Ƿ�ɼ�
	bool visibale = true;
	//���������С
	Size* areaSize;
	//�߿��С
	double borderSize;
	//��ȥ�߿�����ݴ�С---�����ӿؼ����ڴ������ڻ���
	Size* contentSize;
	//�ü��ռ�---ֻ���Ƹ���������ݣ���������������ݽ����ᴦ��
	Size* clipSize;
	Size* globalAreaSize;
	//����������ɫˢ
	Draw::Brush* areaBrush;
	Draw::Brush* borderBrush;
	//���ƶ�������
	double* vertexData;
	//����������
	double* vertexColorData;
	//�߿򶥵�����
	double* borderVertexData;
	//�߿򶥵���ɫ����
	double* borderVertexColorData;
	//������������
	double* textureIndexData;
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
