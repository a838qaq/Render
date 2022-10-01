#include "pch.h"
#include "Point2.h"
#include <iostream>

CPoint2::CPoint2(void)
{
	this->x = 0;
	this->y = 0;
}

CPoint2::~CPoint2(void)
{
}

CPoint2::CPoint2(double x, double y)
{
	this->x = x;
	this->y = y;
}

CPoint2::CPoint2(double x, double y, CRGB c)
{
	this->x = x;
	this->y = y;
	this->c = c;
}

void CPoint2::print()
{
	std::cout << "x = " << this->x << " y = " << this->y << std::endl 
		<< " RGB = " << this->c.alpha << " " << this->c.green << " " << this->c.blue;
}

double CPoint2::cross(CPoint2 p)
{
	return this->x * p.y - this->y * p.x;
}

void CPoint2::getXY(double x, double y)
{
	this->x = x;
	this->y = y;
}

void CPoint2::getXY(CPoint CP)
{
	this->x = CP.x;
	this->y = CP.y;
}



CPoint2 operator+(CPoint2& p1, CPoint2& p2)
{
	return CPoint2(p1.x + p2.x, p1.y + p2.y);
}

CPoint2 operator-(CPoint2& p1, CPoint2& p2)
{
	return CPoint2(p1.x - p2.x, p1.y - p2.y);
}

CPoint2 operator*(double scalar, CPoint2& p)
{
	return CPoint2(scalar * p.x, scalar * p.y);
}

CPoint2 operator*(CPoint2& p, double scalar)
{
	return CPoint2(scalar * p.x, scalar * p.y);
}

CPoint2 operator/(CPoint2& p, double scalar)
{
	return CPoint2(p.x / scalar, p.y / scalar);
}
