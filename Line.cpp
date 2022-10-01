#include "pch.h"
#include "Line.h"

CLine::CLine(void)
{
}

CLine::~CLine(void)
{
}

void CLine::MoveTo(CDC* pDC, CPoint2 p0)
{
	CPoint p(p0.x, p0.y);
	pDC->MoveTo(p);
	this->P0 = p0;
}

void CLine::MoveTo(CDC* pDC, int x0, int y0, CRGB c0)
{
	CPoint p(x0, y0);
	pDC->MoveTo(p);
	this->P0.x = x0;
	this->P0.y = y0;
	this->P0.c = c0;
}

void CLine::LineTo(CDC* pDC, CPoint2 p0)
{
	P1 = p0;
	int dx = abs((P1 - P0).x);
	int dy = abs((P1 - P0).y);
	BOOL bInterChange = FALSE;//x为主位移方向
	int e, signX, signY, temp;

	//确定方向的四大象限
	signX = (P1.x > P0.x ? 1 : (P1.x < P0.x ? -1 : 0));
	signY = (P1.y > P0.y ? 1 : (P1.y < P0.y ? -1 : 0));

	if (dy > dx)
	{
		temp = dx;
		dx = dy;
		dy = temp;
		bInterChange = TRUE;
	}
	e = -dx;
	CPoint2 p = P0;

	for (int i = 1; i <= dx; i++)
	{
		//插值着色
		p.c = LinearInterp(p.x, P0.x, P1.x, P0.c, P1.c);
		if (!signX)
		{
			p.c = LinearInterp(p.y, P0.y, P1.y, P0.c, P1.c);
		}
		pDC->SetPixelV(p.x, p.y, RGB(p.c.red * 255, p.c.green * 255, p.c.blue * 255));

		//选择下一个像素点
		if (bInterChange)
		{
			p.y += signY;
		}
		else
		{
			p.x += signX;
		}
		e += 2 * dy;
		if (e >= 0)
		{
			if (bInterChange)
			{
				p.x += signX;
			}
			else
			{
				p.y += signY;
			}
			e -= 2 * dx;
		}
	}
	//P0 = p0;
}

void CLine::LineTo(CDC* pDC, int x0, int y0, CRGB c0)
{
	LineTo(pDC, CPoint2(x0, y0, c0));
}

CRGB CLine::LinearInterp(double t, double tStart, double tEnd, CRGB cStart, CRGB cEnd)
{
	CRGB coulor = (t - tEnd) / (tStart - tEnd) * cStart + (tStart - t) / (tStart - tEnd) * cEnd;
	return coulor;
}
