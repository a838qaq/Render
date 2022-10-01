#include "pch.h"
#include "FaceT.h"
#include "P3.h"

CFaceT::CFaceT()
{
	this->Number = 3;
	S = 0;
}

CFaceT::~CFaceT()
{
}

void CFaceT::SetIndex(int a, int b, int c)
{
	int A[3] = { a, b, c };
	for (int i = 0; i < Number; i++)
	{
		this->Index[i] = A[i];
	}
}

void CFaceT::SetRGB(double red, double green, double blue)
{
	this->coulor.SetRGB(red, green, blue);
}

void CFaceT::SetNormal(double x, double y, double z)
{
	Normal.getXYZ(x, y, z);
}
