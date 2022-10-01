#pragma once
#include "P3.h"
#include "Face.h"

class CCube
{
public:
	CCube(void);
	virtual ~CCube();
	void ReadPoint();
	void ReadFace();
	CP3* GetPoints();//��ȡ�����
	CP3 GetCenterPoint();//��ȡ��������
	void LoadBuffer();//���뻺��
	CP3* GetBufferPoint();//��ȡ���涥���


	void Draw(CDC *pDC);

public:
	CP3 P[8];
	CFace F[6];

	CP3 bP[8];
};

