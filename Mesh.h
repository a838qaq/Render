#pragma once
#include "Point2.h"

class CMesh
{
public:
	
	CMesh(void);
	CMesh(CPoint2 p0, CPoint2 p1, CPoint2 p2);
	virtual ~CMesh();

	BOOL ifInTriangle(CPoint2 p);
	BOOL ifInTriangle(int x, int y);
	void Rasterization(CDC *pDC, BOOL msaa);
public:
	CPoint2 P0, P1, P2;
	CPoint2 MSAA[4];
};

