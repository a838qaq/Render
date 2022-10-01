#include "pch.h"
#include "Face.h"
#include "P3.h"

CFace::CFace()
{
	this->Number = 4;
}

CFace::~CFace()
{
}

void CFace::SetIndex(int a, int b, int c, int d)
{
	int A[4] = { a, b, c, d };
	for (int i = 0; i < 4; i++)
	{
		this->Index[i] = A[i];
	}
}
