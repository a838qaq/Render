#include "pch.h"
#include "Mesh.h"

BOOL CMesh::ifInTriangle(CPoint2 p)
{
	//ºÃÏñ»¹ÓÐbug
	CPoint2 AP = p - P0;
	CPoint2 BP = p - P1;
	CPoint2 CP = p - P2;
	CPoint2 AB = P1 - P0;
	CPoint2 BC = P2 - P1;
	CPoint2 CA = P0 - P2;
	double a = AP.x * AB.y - AP.y * AB.x;
	double b = AP.x * BC.y - AP.y * BC.x;
	double c = AP.x * CA.y - AP.y * BC.x;

	if ((a < 0 && b < 0 && c < 0) || (a > 0 && b > 0 && c > 0))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CMesh::ifInTriangle(int x, int y)
{
	return ifInTriangle(CPoint2(x,y));
}

void CMesh::Rasterization(CDC *pDC, BOOL msaa)
{

	int MAX_x = fmax(this->P0.x, fmax(this->P1.x, this->P2.x));
	int MAX_y = fmax(this->P0.y, fmax(this->P1.y, this->P2.y));
	int MIN_x = fmin(this->P0.x, fmin(this->P1.x, this->P2.x));
	int MIN_y = fmin(this->P0.y, fmin(this->P1.y, this->P2.y));
	CPoint2 p0 = this->P0;
	CPoint2 p1 = this->P1;
	CPoint2 p2 = this->P2;
	for (int i = MIN_x; i <= MAX_x; i++)
	{
		for (int j = MIN_y; j <= MAX_y; j++)
		{
			if (!msaa)
			{
				double a = ((-(i - p1.x) * (p2.y - p1.y) + (j - p1.y) * (p2.x - p1.x)) /
						(-(p0.x - p1.x) * (p2.y - p1.y) + (p0.y - p1.y) * (p2.x - p1.x)));
				double b = ((-(i - p2.x) * (p0.y - p2.y) + (j - p2.y) * (p0.x - p2.x)) /
						(-(p1.x - p2.x) * (p0.y - p2.y) + (p1.y - p2.y) * (p0.x - p2.x)));
				double c = 1 - a - b;
				if(a > 0 && b > 0 && c > 0 && a < 1 && b < 1 && c < 1)
				{
					CRGB coulor(a * P0.c.red, b * P1.c.green, c * P2.c.blue);
					pDC->MoveTo(i, j);
					pDC->SetPixelV(i, j, RGB(abs(coulor.red * 255), abs(coulor.green * 255), abs(coulor.blue * 255)));
				}
			}
			else
			{
				CRGB coulor[4];
				double a, b, c;
				for (int k = 0; k <= 3; k++)
				{
					a = ((-(i + MSAA[k].x - p1.x) * (p2.y - p1.y) + (j + MSAA[k].y - p1.y) * (p2.x - p1.x)) /
						(-(p0.x - p1.x) * (p2.y - p1.y) + (p0.y - p1.y) * (p2.x - p1.x)));
					b = ((-(i + MSAA[k].x - p2.x) * (p0.y - p2.y) + (j + MSAA[k].y - p2.y) * (p0.x - p2.x)) /
						(-(p1.x - p2.x) * (p0.y - p2.y) + (p1.y - p2.y) * (p0.x - p2.x)));
					c = 1 - a - b;
					coulor[k].red = a * P0.c.red;
					coulor[k].green = b * P1.c.green;
					coulor[k].blue = c * P2.c.blue;
				}
				if (a > 0 && b > 0 && c > 0 && a < 1 && b < 1 && c < 1)
				{
					CRGB COULOR = (coulor[0] + coulor[1] + coulor[2] + coulor[3]) / 4;
					pDC->MoveTo(i, j);
					pDC->SetPixelV(i, j, RGB(abs(COULOR.red * 255), abs(COULOR.green * 255), abs(COULOR.blue * 255)));
				}
			}
		} 
	}
}

CMesh::CMesh(void)
{
	MSAA[0] = MSAA[0] + CPoint2(0.25, 0.25);
	MSAA[1] = MSAA[1] + CPoint2(0.25, 0.75);
	MSAA[2] = MSAA[2] + CPoint2(0.75, 0.25);
	MSAA[3] = MSAA[3] + CPoint2(0.75, 0.75);

}

CMesh::CMesh(CPoint2 p0, CPoint2 p1, CPoint2 p2)
{
	this->P0 = p0;
	this->P1 = p1;
	this->P2 = p2;
	MSAA[0] = MSAA[0] + CPoint2(0.25, 0.25);
	MSAA[1] = MSAA[1] + CPoint2(0.25, 0.75);
	MSAA[2] = MSAA[2] + CPoint2(0.75, 0.25);
	MSAA[3] = MSAA[3] + CPoint2(0.75, 0.75);
}

CMesh::~CMesh()
{
}
