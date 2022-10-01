#pragma once
#include "RGB.h"

class CPoint2
{
public:
	CPoint2(void);
	virtual ~CPoint2(void);
	CPoint2(double x, double y);
	CPoint2(double x, double y, CRGB c);

	friend CPoint2 operator + (CPoint2& p1, CPoint2& p2);
	friend CPoint2 operator - (CPoint2& p1, CPoint2& p2);
	friend CPoint2 operator * (double scalar, CPoint2& p);
	friend CPoint2 operator * (CPoint2& p, double scalar);
	friend CPoint2 operator / (CPoint2& p, double scalar);
	//friend CPoint2 operator = (CPoint2& p1, CPoint2& p2);
	void print();
	double cross(CPoint2 p);
	void getXY(double x, double y);
	void getXY(CPoint CP);
public:
	double x;
	double y;
	CRGB c;
};

