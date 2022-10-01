#pragma once
#include "P3.h"
#include "RGB.h"

class CFaceT
{
public:
	CFaceT();
	virtual ~CFaceT();
	void SetIndex(int a, int b, int c);
	void SetRGB(double red, double green, double blue);
	void SetNormal(double x, double y, double z);

public:
	int Number;//顶点数目
	int Index[3];//顶点索引
	CRGB coulor;//面色
	CP3 Normal;//法线向量
	double S;//面积
};

