#include "pch.h"
#include "UI.h"

CUI::CUI()
{
	Mode = 1;
	RasterMode = 1;
}

CUI::~CUI()
{
}

int CUI::GetMode()
{
	return Mode;
}

void CUI::SetModeModel()
{
	Mode = 0;
}

void CUI::SetModeCamera()
{
	Mode = 1;
}

int CUI::GetRasterMode()
{
	return RasterMode;
}

void CUI::SetRasterOrth()
{
	RasterMode = 0;
}

void CUI::SetRasterPers()
{
	RasterMode = 1;
}

void CUI::Draw(CDC* pDC, int nHeight, int nWidth)
{
		CBrush NewBrush, * pOldBrush;
		NewBrush.CreateSolidBrush(RGB(255, 0, 0));
		pOldBrush = pDC->SelectObject(&NewBrush);
		pDC->Rectangle(CRect(CPoint(nWidth * 0.4, nHeight * 0.5), CPoint(nWidth * 0.5, nHeight * 0.4)));
		NewBrush.DeleteObject();

		NewBrush.CreateSolidBrush(RGB(0, 255, 0));
		pOldBrush = pDC->SelectObject(&NewBrush);
		pDC->Rectangle(CRect(CPoint(nWidth * 0.3, nHeight * 0.5), CPoint(nWidth * 0.4, nHeight * 0.4)));
		NewBrush.DeleteObject();
		
		pOldBrush->DeleteObject();
}
