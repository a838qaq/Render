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
	int Number;//������Ŀ
	int Index[3];//��������
	CRGB coulor;//��ɫ
	CP3 Normal;//��������
	double S;//���
};

