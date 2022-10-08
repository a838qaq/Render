#pragma once
#include "P3.h"

class CCamera
{
public:
	CCamera();
	void SetPosition(double x, double y, double z);
	void SetDirector(double x, double y, double z);
	void SetHead(double x, double y, double z);
	void SetN(double n);
	void SetF(double f);

	CP3* GetPositonPoint();
	CP3* GetDirectorPoint();
	CP3* GetHeadPoint();
	double* GetZbuffer();
	int GetZbufferMax();
	void InitZbuffer();
	void MoreWide();
	void MoreNarrow();

public:
	CP3 Position;//�����λ��
	CP3 Director;//�������ָ��
	CP3 Head;//�������ͷ������
	double n;//ͶӰ��ƽ��
	double f;//����Զƽ��
	double Zbuffer[5000000];//Zbuffer
	int ZbufferMax;//Zbuffer���ֵ
};

