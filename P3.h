#pragma once
#include "Point2.h"
class CP3 : public CPoint2
{
public:
	CP3(void);
	CP3(double x, double y, double z);
	virtual ~CP3();
	void getXYZ(double x, double y, double z);
	void normalization();//��λ��
	CP3 Cross(CP3 P);//���
	double Dot(CP3 P);//���
	double GetLenth();//ȡģ
	void StdPoint();//w��һ��
	double GetLenth2();//ȡģ��
	void SetRGB(double red, double green, double blue);//����RGB

	friend CP3 operator + (CP3 P1, CP3 P2);
	friend CP3 operator - (CP3 P1, CP3 P2);
	friend CP3 operator * (CP3 P1, double scalar);
	friend CP3 operator * (double scalar, CP3 P1);
	friend CP3 operator / (CP3 P, double scalar);

public:
	double z;
	double w;
};

