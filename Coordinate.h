#pragma once
#include "P3.h"


class CCoordinate
{
public:
	CCoordinate();
	virtual ~CCoordinate();
	CP3* GetPoint();//��ȡ�����
	void Draw(CDC* pDC);//����
	void LoadBufferPoint();//���뻺��
	CP3* GetBufferPoint();//��ȡ���涥���

public:
	CP3 P[4];
	int PNumber;

	CP3 bP[4];
};

