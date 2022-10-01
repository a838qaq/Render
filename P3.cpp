#include "pch.h"
#include "P3.h"
#include <cmath>

CP3::CP3(void)
{
	x = y = z = 0;
	w = 1;
}

CP3::CP3(double x, double y, double z) : CPoint2(x, y)
{
	this->z = z;
	this->w = 1;
}

CP3::~CP3()
{
}

void CP3::getXYZ(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void CP3::normalization()
{
	CP3 temp = *this;
	this->x = temp.x / sqrt(temp.x * temp.x + temp.y * temp.y + temp.z * temp.z);
	this->y = temp.y / sqrt(temp.x * temp.x + temp.y * temp.y + temp.z * temp.z);
	this->z = temp.z / sqrt(temp.x * temp.x + temp.y * temp.y + temp.z * temp.z);
}

CP3 CP3::Cross(CP3 P)
{
	return CP3(y * P.z - z * P.y, -x * P.z + z * P.x, x * P.y - y * P.x);
}

double CP3::Dot(CP3 P)
{
	return this->x * P.x + this->y * P.y + this->z * P.z;
}

double CP3::GetLenth()
{
	return sqrt(x * x + y * y + z * z);
}

void CP3::StdPoint()
{
	x /= w;
	y /= w;
	z /= w;
	w /= w;
}

double CP3::GetLenth2()
{
	return x * x + y * y + z * z;
}

void CP3::SetRGB(double red, double green, double blue)
{
	c.red = red;
	c.green = green;
	c.blue = blue;
}

CP3 operator+(CP3 P1, CP3 P2)
{
	return CP3(P1.x + P2.x, P1.y + P2.y, P1.z + P2.z);
}

CP3 operator-(CP3 P1, CP3 P2)
{
	return CP3(P1.x - P2.x, P1.y - P2.y, P1.z - P2.z);
}

CP3 operator*(CP3 P1, double scalar)
{
	return CP3(P1.x * scalar, P1.y * scalar, P1.z * scalar);
}

CP3 operator*(double scalar, CP3 P1)
{
	return CP3(P1.x * scalar, P1.y * scalar, P1.z * scalar);
}

CP3 operator/(CP3 P, double scalar)
{
	return CP3(P.x / scalar, P.y / scalar, P.z / scalar);
}
