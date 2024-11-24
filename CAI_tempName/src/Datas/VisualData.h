#pragma once
#include "Object.h"
#include "Datas/Coordinate.h"
#include "UI/Draw.h"
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
	inline Size& AreaSize()  noexcept { return areaSize; }
	inline Size& ClipSize()  noexcept { return clipSize; }
	inline Size& ContentSize()  noexcept { return contentSize; }
	inline Size& GlobalAreaSize()  noexcept { return globalAreaSize; }
	inline Draw::Brush& AreaBrush()  noexcept { return areaBrush; }
	void SetBorderSize(float value) noexcept;
	void InitData();
public:
	bool isDataHasBeenPushToGpu;
	bool hasBorder;
	bool needClip;
private:
	friend class PaintDevice;
	friend class UIElement;
	friend class Control;
	//���������С
	Size areaSize;
	//�߿��С
	float borderSize;
	//��ȥ�߿�����ݴ�С---�����ӿؼ����ڴ������ڻ���
	Size contentSize;
	//�ü��ռ�---ֻ���Ƹ���������ݣ���������������ݽ����ᴦ��
	Size clipSize;
	Size globalAreaSize;
	//����������ɫˢ
	Draw::Brush areaBrush;
	Draw::Brush borderBrush;
	//�����������Ͻ�����
	float originVertexData[3];
	float bordderVertexData[3];
	//���δ�С����
	float rectSizeData[2];
	float borderRectSizeData[2];
	//����������
	float borderColorData[4];
	float colorData[4];
	
	//�߿�Ļ�������--ʵ���ϱ߿�Ļ��������ǿؼ�����Size�����������ģ�������������������Ļ���
	//�߿�Ļ��ƿ��������ؼ���Ӱ�Ļ���---��Ҫע�����������������Ϊ����ģ���������ᵼ������Ҳ�ܹ�������ӰЧ���������������Ҳ����Ӱ��ô��Ҫ���⴦��������Ⱦ���

	//�������ݸ���
	//unsigned int vertexSize;
	//�������ݸ���
	//unsigned int indexSize;
	//��ʱ�������������������Ҫ���ò�ͬ����ɫ��
	////content������ID
	//unsigned int texture;
	////�߿������ID
	//unsigned int textureBorder;
};
