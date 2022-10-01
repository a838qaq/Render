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
	CP3* GetPoints();//获取顶点表
	CP3 GetCenterPoint();//获取中心坐标
	void LoadBuffer();//读入缓存
	CP3* GetBufferPoint();//获取缓存顶点表


	void Draw(CDC *pDC);

public:
	CP3 P[8];
	CFace F[6];

	CP3 bP[8];
};

