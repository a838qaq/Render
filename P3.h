#pragma once
#include "Point2.h"
class CP3 : public CPoint2
{
public:
	CP3(void);
	CP3(double x, double y, double z);
	virtual ~CP3();
	void getXYZ(double x, double y, double z);
	void normalization();//单位化
	CP3 Cross(CP3 P);//叉乘
	double Dot(CP3 P);//点乘
	double GetLenth();//取模
	void StdPoint();//w归一化
	double GetLenth2();//取模方
	void SetRGB(double red, double green, double blue);//设置RGB

	friend CP3 operator + (CP3 P1, CP3 P2);
	friend CP3 operator - (CP3 P1, CP3 P2);
	friend CP3 operator * (CP3 P1, double scalar);
	friend CP3 operator * (double scalar, CP3 P1);
	friend CP3 operator / (CP3 P, double scalar);

public:
	double z;
	double w;
};

