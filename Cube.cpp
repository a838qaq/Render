#include "pch.h"
#include "Cube.h"

CCube::CCube(void)
{
}

CCube::~CCube()
{
}

void CCube::ReadPoint()
{
	P[0].getXYZ(-50, 50, 100);
	P[1].getXYZ(50, 50, 100);
	P[2].getXYZ(50, 50, 0);
	P[3].getXYZ(-50, 50, 0);
	P[4].getXYZ(-50, -50, 100);
	P[5].getXYZ(50, -50, 100);
	P[6].getXYZ(50, -50, 0);
	P[7].getXYZ(-50, -50, 0);
}

void CCube::ReadFace()
{
	F[0].SetIndex(0, 1, 2, 3);
	F[1].SetIndex(4, 5, 6, 7);
	F[2].SetIndex(0, 1, 5, 4);
	F[3].SetIndex(3, 2, 6, 7);
	F[4].SetIndex(0, 3, 7, 4);
	F[5].SetIndex(1, 2, 6, 5);
}

CP3* CCube::GetPoints()
{
	return P;
}

CP3 CCube::GetCenterPoint()
{
	return CP3((P[0].x + P[6].x) / 2, (P[0].y + P[6].y) / 2, (P[0].z + P[6].z) / 2);
}

void CCube::LoadBuffer()
{
	for (int i = 0; i < 8; i++)
	{
		bP[i] = P[i];
	}
}

CP3* CCube::GetBufferPoint()
{
	return bP;
}

void CCube::Draw(CDC *pDC)
{
	CPoint2 ScreemPoint, temp;
	for (int iFace = 0; iFace < 6; iFace++)
	{
		for (int iPoint = 0; iPoint < 4; iPoint++)
		{
			ScreemPoint.getXY(this->bP[F[iFace].Index[iPoint]].x, this->bP[F[iFace].Index[iPoint]].y);//选中当前点
			if (iPoint == 0)
			{
				pDC->MoveTo(ScreemPoint.x, ScreemPoint.y);
				temp = ScreemPoint;
			}
			else
			{
				pDC->LineTo(ScreemPoint.x, ScreemPoint.y);
			}
		//	pDC->Ellipse(ScreemPoint.x - 5*iPoint, ScreemPoint.y - 5*iPoint, ScreemPoint.x + 5*iPoint, ScreemPoint.y + 5*iPoint);
		}
		pDC->LineTo(temp.x, temp.y);
	}
}
