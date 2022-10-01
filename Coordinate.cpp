#include "pch.h"
#include "Coordinate.h"

CCoordinate::CCoordinate()
{
	P[0].getXYZ(0, 0, 0);
	P[1].getXY(1000, 0.0);
	P[2].getXYZ(0, 1000, 0);
	P[3].getXYZ(0, 0, 1000);
	PNumber = 4;
}

CCoordinate::~CCoordinate()
{
}

CP3* CCoordinate::GetPoint()
{
	return P;
}

void CCoordinate::Draw(CDC* pDC)
{
	pDC->MoveTo(bP[0].x, bP[0].y);
	pDC->LineTo(bP[1].x, bP[1].y);
	pDC->MoveTo(bP[0].x, bP[0].y);
	pDC->LineTo(bP[2].x, bP[2].y);
	pDC->MoveTo(bP[0].x, bP[0].y);
	pDC->LineTo(bP[3].x, bP[3].y);
}

void CCoordinate::LoadBufferPoint()
{
	for (int i = 0; i < 4; i++)
	{
		bP[i] = P[i];
	}
}

CP3* CCoordinate::GetBufferPoint()
{
	return bP;
}
