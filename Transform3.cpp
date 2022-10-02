#include "pch.h"
#include "Transform3.h"
#include <cmath>
#define PI 3.14159265358979

void CTransform3::Init()
{
	Matrix[0][0] = 1; Matrix[0][1] = 0; Matrix[0][2] = 0; Matrix[0][3] = 0;
	Matrix[1][0] = 0; Matrix[1][1] = 1; Matrix[1][2] = 0; Matrix[1][3] = 0;
	Matrix[2][0] = 0; Matrix[2][1] = 0; Matrix[2][2] = 1; Matrix[2][3] = 0;
	Matrix[3][0] = 0; Matrix[3][1] = 0; Matrix[3][2] = 0; Matrix[3][3] = 1;
}

void CTransform3::MultiplyMatrix()
{
	CP3 *pTemp = new CP3[PNumber];
	for (int i = 0; i < PNumber; i++)
	{
		pTemp[i] = P[i];
	}
	for (int i = 0; i < PNumber; i++)
	{
		P[i].x = Matrix[0][0] * pTemp[i].x + Matrix[0][1] * pTemp[i].y + Matrix[0][2] * pTemp[i].z + Matrix[0][3] * pTemp[i].w;
		P[i].y = Matrix[1][0] * pTemp[i].x + Matrix[1][1] * pTemp[i].y + Matrix[1][2] * pTemp[i].z + Matrix[1][3] * pTemp[i].w;
		P[i].z = Matrix[2][0] * pTemp[i].x + Matrix[2][1] * pTemp[i].y + Matrix[2][2] * pTemp[i].z + Matrix[2][3] * pTemp[i].w;
		P[i].w = Matrix[3][0] * pTemp[i].x + Matrix[3][1] * pTemp[i].y + Matrix[3][2] * pTemp[i].z + Matrix[3][3] * pTemp[i].w;
		P[i].StdPoint();
	}
	delete []pTemp;
}

void CTransform3::MultiplyMatrixForTranslate()
{
	int temp = PNumber;
	if (PNumber > 4)
	{
		temp -= FnNumber;
	}
	
	CP3* pTemp = new CP3[temp];
	for (int i = 0; i < temp; i++)
	{
		pTemp[i] = P[i];
	}
	for (int i = 0; i < temp; i++)
	{
		P[i].x = Matrix[0][0] * pTemp[i].x + Matrix[0][1] * pTemp[i].y + Matrix[0][2] * pTemp[i].z + Matrix[0][3] * pTemp[i].w;
		P[i].y = Matrix[1][0] * pTemp[i].x + Matrix[1][1] * pTemp[i].y + Matrix[1][2] * pTemp[i].z + Matrix[1][3] * pTemp[i].w;
		P[i].z = Matrix[2][0] * pTemp[i].x + Matrix[2][1] * pTemp[i].y + Matrix[2][2] * pTemp[i].z + Matrix[2][3] * pTemp[i].w;
		P[i].w = Matrix[3][0] * pTemp[i].x + Matrix[3][1] * pTemp[i].y + Matrix[3][2] * pTemp[i].z + Matrix[3][3] * pTemp[i].w;
		P[i].StdPoint();
	}
	delete[]pTemp;
}

void CTransform3::SetMatrix(CP3* P, int Number)
{
	this->P = P;
	this->PNumber = Number;
}

void CTransform3::SetFnNumber(int FnNumber)
{
	this->FnNumber = FnNumber;
}

void CTransform3::Translate(double tx, double ty, double tz)
{
	Init();
	Matrix[0][3] = tx;
	Matrix[1][3] = ty;
	Matrix[2][3] = tz;
	MultiplyMatrixForTranslate();
}

void CTransform3::Scale(double sx, double sy, double sz)
{
	Init();
	Matrix[0][0] = sx;
	Matrix[1][1] = sy;
	Matrix[2][2] = sz;
	MultiplyMatrixForTranslate();
}

void CTransform3::RotateX(double angle)
{
	Init();
	double rad = angle / 180 * PI;
	Matrix[1][1] = cos(rad); Matrix[1][2] = -sin(rad);
	Matrix[2][1] = sin(rad); Matrix[2][2] = cos(rad);
	MultiplyMatrix();
}

void CTransform3::RotateY(double angle)
{
	Init();
	double rad = angle / 180 * PI;
	Matrix[0][0] = cos(rad); Matrix[0][2] = sin(rad);
	Matrix[2][0] = -sin(rad); Matrix[2][2] = cos(rad);
	MultiplyMatrix();
}

void CTransform3::RotateZ(double angle)
{
	Init();
	double rad = angle / 180 * PI;
	Matrix[0][0] = cos(rad); Matrix[0][1] = -sin(rad);
	Matrix[1][0] = sin(rad); Matrix[1][1] = cos(rad);
	MultiplyMatrix();

}

void CTransform3::RotateThisX(double angle, CP3 CenterPoint)
{
	this->Translate(-CenterPoint.x, -CenterPoint.y, -CenterPoint.z);
	this->RotateX(angle);
	this->Translate(CenterPoint.x, CenterPoint.y, CenterPoint.z);
}

void CTransform3::RotateThisY(double angle, CP3 CenterPoint)
{
	this->Translate(-CenterPoint.x, -CenterPoint.y, -CenterPoint.z);
	this->RotateY(angle);
	this->Translate(CenterPoint.x, CenterPoint.y, CenterPoint.z);

}

void CTransform3::RotateThisZ(double angle, CP3 CenterPoint)
{
	this->Translate(-CenterPoint.x, -CenterPoint.y, -CenterPoint.z);
	this->RotateZ(angle);
	this->Translate(CenterPoint.x, CenterPoint.y, CenterPoint.z);

}

void CTransform3::RotateByCamera(CP3 Posision, CP3 Director, CP3 Head)
{
	CP3 w = Director / Director.GetLenth();
	CP3 u = Head.Cross(w) / Head.Cross(w).GetLenth();
	CP3 v = w.Cross(u);
	Init();
	Matrix[0][0] = u.x; Matrix[0][1] = u.y; Matrix[0][2] = u.z;
	Matrix[1][0] = v.x; Matrix[1][1] = v.y; Matrix[1][2] = v.z;
	Matrix[2][0] = w.x; Matrix[2][1] = w.y; Matrix[2][2] = w.z;
	MultiplyMatrix();
}

void CTransform3::Perspective(double n, double f)
{
	Init();
	Matrix[0][0] = n;
						Matrix[1][1] = n;
											Matrix[2][2] = n + f;	Matrix[2][3] = -f * n;
											Matrix[3][2] = 1;
	MultiplyMatrix();
}

void CTransform3::Orthographic()
{
	Init();
	Matrix[3][3] = -1;
	MultiplyMatrix();
}

