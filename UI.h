#pragma once
class CUI
{
public:
	CUI();
	virtual ~CUI();

	int GetMode();//���ص�ǰ����ģʽ
	void SetModeModel();//����Ϊ����ģ��
	void SetModeCamera();//����Ϊ�������
	
	int GetRasterMode();//���ص�ǰ��Ⱦģʽ
	void SetRasterOrth();//����Ϊ����ͶӰ
	void SetRasterPers();//����Ϊ͸��ͶӰ

	void Draw(CDC* pDC, int nHeight, int nWidth);//����UI

public:
	int Mode;//��ǰ����ģʽ
	int RasterMode;//��ǰ͸��ģʽ
};

