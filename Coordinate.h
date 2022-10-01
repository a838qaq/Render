#pragma once
#include "P3.h"


class CCoordinate
{
public:
	CCoordinate();
	virtual ~CCoordinate();
	CP3* GetPoint();//获取顶点表
	void Draw(CDC* pDC);//绘制
	void LoadBufferPoint();//读入缓存
	CP3* GetBufferPoint();//获取缓存顶点表

public:
	CP3 P[4];
	int PNumber;

	CP3 bP[4];
};

