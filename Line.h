#pragma once
#include "Point2.h"

class CLine
{
public:
	CLine(void);
	virtual ~CLine(void);

	void MoveTo(CDC* pDC, CPoint2 p0);
	void MoveTo(CDC* pDC, int x0, int y0, CRGB c0);
	void LineTo(CDC* pDC, CPoint2 p0);
	void LineTo(CDC* pDC, int x0, int y0, CRGB c0);
	CRGB LinearInterp(double t, double tStart, double tEnd, CRGB cStart, CRGB cEnd);

private:
	CPoint2 P0;
	CPoint2 P1;
	
};

