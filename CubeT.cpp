#include "pch.h"
#include "CubeT.h"
#include <cmath>

CCubeT::CCubeT(void)
{
	DrawMode = 3;
	PNumber = 8 + 12;
	FNumber = 12;
	for (int i = 0; i < 12; i++)
	{
		VisionableFace[i] = 1;
	}
	SSAA = FALSE;
	MSAA[0].getXY(0.25, 0.25);
	MSAA[1].getXY(0.25, 0.75);
	MSAA[2].getXY(0.75, 0.25);
	MSAA[3].getXY(0.75, 0.75);
}

CCubeT::~CCubeT()
{
}

void CCubeT::ReadPoint()
{
	P[0].getXYZ(-50, 50, 100);
	P[1].getXYZ(50, 50, 100);
	P[2].getXYZ(50, 50, 0);
	P[3].getXYZ(-50, 50, 0);
	P[4].getXYZ(-50, -50, 100);
	P[5].getXYZ(50, -50, 100);
	P[6].getXYZ(50, -50, 0);
	P[7].getXYZ(-50, -50, 0);
	for (int i = 8; i < 20; i++)
	{
		P[i] = F[i - 8].Normal;
	}
}

void CCubeT::Init()
{
	ReadFace();
	ReadPoint();
	SetFaceRGB();
	SetTriangleRGB();
	SetPointRGB();
}

void CCubeT::ReadFace()
{
	F[0].SetIndex(0, 1, 3); F[0].SetNormal(0, 1, 0);	//右面
	F[1].SetIndex(1, 2, 3); F[1].SetNormal(0, 1, 0);
	F[2].SetIndex(4, 5, 6); F[2].SetNormal(0, -1, 0);	//左面
	F[3].SetIndex(4, 6, 7); F[3].SetNormal(0, -1, 0);
	F[4].SetIndex(0, 1, 4); F[4].SetNormal(0, 0, 1);	//上面
	F[5].SetIndex(1, 5, 4); F[5].SetNormal(0, 0, 1);
	F[6].SetIndex(2, 3, 6); F[6].SetNormal(0, 0, -1);	//下面
	F[7].SetIndex(3, 6, 7); F[7].SetNormal(0, 0, -1);
	F[8].SetIndex(0, 3, 4); F[8].SetNormal(-1, 0, 0);	//后面
	F[9].SetIndex(3, 7, 4); F[9].SetNormal(-1, 0, 0);
	F[10].SetIndex(1, 2, 6); F[10].SetNormal(1, 0, 0);	//前面
	F[11].SetIndex(1, 5, 6); F[11].SetNormal(1, 0, 0);
}

CP3* CCubeT::GetPoints()
{
	return P;
}

CP3 CCubeT::GetCenterPoint()
{
	return CP3((P[0].x + P[6].x) / 2, (P[0].y + P[6].y) / 2, (P[0].z + P[6].z) / 2);
}

void CCubeT::LoadBuffer()
{
	for (int i = 0; i < 8; i++)
	{
		bP[i] = P[i];
	}
}

void CCubeT::LoadPointNormal()
{
	LoadFaceS();
	for (int i = 0; i < PNumber - FNumber; i++)
	{
		CP3 vector(0,0,0);
		double SumS = 0;
		for (int j = 0; j < FNumber; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (F[j].Index[k] == i)
				{
					SumS += F[j].S;
					vector = vector + F[j].S * P[PNumber - FNumber + j];
				}	
			}
		}
		nP[i] = (vector / SumS);
		nP[i].normalization();
	}
}

CP3* CCubeT::GetBufferPoint()
{
	return bP;
}

void CCubeT::DeletFace(CP3 CameraPosition, int flag)
{
	if (flag)
	{
		for (int i = 0; i < FNumber; i++)
		{
			if ((P[F[i].Index[0]]-CameraPosition).Dot(P[i + PNumber - FNumber]) > 0)
			{
				VisionableFace[i] = 0;
			}
			else
			{
				VisionableFace[i] = 1;
			}
		}
	}
}

void CCubeT::LoadFaceS()
{
	for (int i = 0; i < FNumber; i++)
	{
		double a = (P[F[i].Index[0]] - P[F[i].Index[1]]).GetLenth();
		double b = (P[F[i].Index[1]] - P[F[i].Index[2]]).GetLenth();
		double c = (P[F[i].Index[2]] - P[F[i].Index[0]]).GetLenth();
		double p = (a + b + c) / 2;
		F[i].S = sqrt(p * (p - 1) * (p - b) * (p - c));
	}
}

void CCubeT::SetModeLineFrame()
{
	this->DrawMode = 0;
}

void CCubeT::SetModeFace()
{
	this->DrawMode = 1;
}

void CCubeT::SetModeTriangle()
{
	DrawMode = 2;
}

void CCubeT::SetModePhong()
{
	DrawMode = 3;
}

void CCubeT::SetModeRGBBB()
{
	DrawMode = 4;
}

void CCubeT::SetDepth()
{
	DrawMode = 5;
}

void CCubeT::SetFaceRGB()
{
	F[0].SetRGB(1, 0, 0);		F[1].SetRGB(1, 0, 0);
	F[2].SetRGB(0.5, 0.5, 0);	F[3].SetRGB(0.5, 0.5, 0);
	F[4].SetRGB(0, 1, 0);		F[5].SetRGB(0, 1, 0);
	F[6].SetRGB(0, 0.5, 0.5);	F[7].SetRGB(0, 0.5, 0.5);
	F[8].SetRGB(0, 0, 1);		F[9].SetRGB(0, 0, 1);
	F[10].SetRGB(0.5, 0, 0.5);	F[11].SetRGB(0.5, 0, 0.5);
}

void CCubeT::SetTriangleRGB()
{
	F[0].SetRGB(1, 0, 0);		F[1].SetRGB(1, 0.5, 0);
	F[2].SetRGB(0.5, 0.5, 0);	F[3].SetRGB(0.5, 0.5, 0.5);
	F[4].SetRGB(0, 1, 0);		F[5].SetRGB(0, 1, 0.5);
	F[6].SetRGB(0, 0.5, 0.5);	F[7].SetRGB(0.25, 0.5, 0.5);
	F[8].SetRGB(0, 0, 1);		F[9].SetRGB(0, 0.5, 1);
	F[10].SetRGB(0.5, 0, 0.5);	F[11].SetRGB(0.5, 1, 0.5);
}

void CCubeT::SetPointRGB()
{
	P[0].SetRGB(0, 0, 1);		P[1].SetRGB(0, 1, 0);
	P[2].SetRGB(0, 0, 1);		P[3].SetRGB(0, 1, 0);
	P[4].SetRGB(0, 1, 0);		P[5].SetRGB(0, 0, 1);
	P[6].SetRGB(0, 1, 0);		P[7].SetRGB(0, 0, 1);
}

int CCubeT::GetMode()
{
	return DrawMode;
}

void CCubeT::Draw(CDC* pDC, double* Zbuffer, CP3 CameraPosition, CLighting lighting)
{
	if (DrawMode == 0)
	{
		CPoint2 ScreemPoint, temp;

		int LastIndex = 0;

		for (int iFace = 0; iFace < FNumber; iFace++)
		{
			//背面剔除
			if (VisionableFace[iFace] == 0)
			{
				continue;
			}
			int ifLine[10][10] = { 0 };//加速结构
			for (int iPoint = 0; iPoint < 3; iPoint++)
			{
				ScreemPoint.getXY(this->bP[F[iFace].Index[iPoint]].x, this->bP[F[iFace].Index[iPoint]].y);//绘制屏幕点
				if (iPoint == 0)
				{
					pDC->MoveTo((int)ScreemPoint.x, (int)ScreemPoint.y);
					temp = ScreemPoint;
					LastIndex = F[iFace].Index[iPoint];
				}
				else
				{
					if (ifLine[LastIndex][F[iFace].Index[iPoint]] == 0 && ifLine[F[iFace].Index[iPoint]][LastIndex] == 0)
					{
						pDC->LineTo((int)ScreemPoint.x, (int)ScreemPoint.y);
						ifLine[LastIndex][F[iFace].Index[iPoint]] = 1;
						ifLine[F[iFace].Index[iPoint]][LastIndex] = 1;
						LastIndex = F[iFace].Index[iPoint];
					}
				}
			}
			pDC->LineTo(temp.x, temp.y);
		}
	}
	else if (DrawMode == 1)
	{
		SetFaceRGB();
		for (int iFace = 0; iFace < FNumber; iFace++)
		{
			//背面剔除
			if (VisionableFace[iFace] == 0)
			{
				continue;
			}
			Rasterization(pDC, FALSE, SSAA, iFace, Zbuffer);
		}
	}
	else if (DrawMode == 2)
	{
		SetTriangleRGB();
		for (int iFace = 0; iFace < FNumber; iFace++)
		{
			//背面剔除
			if (VisionableFace[iFace] == 0)
			{
				continue;
			}
			Rasterization(pDC, FALSE, SSAA, iFace, Zbuffer);
		}
	}
	else if (DrawMode == 3)
	{
		//带光照的
		for (int iFace = 0; iFace < FNumber; iFace++)
		{
			if (VisionableFace[iFace] == 0)
			{
				continue;
			}
			Rasterization(pDC, FALSE, SSAA, iFace, Zbuffer, CameraPosition, lighting);
		}
	}
	else if (DrawMode == 4)
	{
		for (int iFace = 0; iFace < FNumber; iFace++)
		{
			if (VisionableFace[iFace]==0)
			{
				continue;
			}
			Rasterization(pDC,TRUE, SSAA, iFace, Zbuffer);
		}
	}
	else if (DrawMode == 5)
	{
		for (int iFace = 0; iFace < FNumber; iFace++)
		{
			if (VisionableFace[iFace] == 0)
			{
				continue;
			}
			Rasterization(pDC, iFace, Zbuffer, CameraPosition, lighting);
		}
	}
}


void CCubeT::Rasterization(CDC* pDC, BOOL ifLinearInterp, BOOL SSAA, int iFace, double* Zbuffer)
{
	int MAX_x = fmax(bP[F[iFace].Index[0]].x, fmax(bP[F[iFace].Index[1]].x, bP[F[iFace].Index[2]].x));
	int MAX_y = fmax(bP[F[iFace].Index[0]].y, fmax(bP[F[iFace].Index[1]].y, bP[F[iFace].Index[2]].y));
	int MIN_x = fmin(bP[F[iFace].Index[0]].x, fmin(bP[F[iFace].Index[1]].x, bP[F[iFace].Index[2]].x));
	int MIN_y = fmin(bP[F[iFace].Index[0]].y, fmin(bP[F[iFace].Index[1]].y, bP[F[iFace].Index[2]].y));

	CP3 p0 = bP[F[iFace].Index[0]];
	CP3 p1 = bP[F[iFace].Index[1]];
	CP3 p2 = bP[F[iFace].Index[2]];

	for (int i = MIN_x; i <= MAX_x; i++)
	{
		for (int j = MIN_y; j <= MAX_y; j++)
		{
			if (!SSAA)
			{
				double a = ((-(i - p1.x) * (p2.y - p1.y) + (j - p1.y) * (p2.x - p1.x)) /
					(-(p0.x - p1.x) * (p2.y - p1.y) + (p0.y - p1.y) * (p2.x - p1.x)));
				double b = ((-(i - p2.x) * (p0.y - p2.y) + (j - p2.y) * (p0.x - p2.x)) /
					(-(p1.x - p2.x) * (p0.y - p2.y) + (p1.y - p2.y) * (p0.x - p2.x)));
				double c = 1 - a - b;
				if (a > 0 && b > 0 && c > 0 && a < 1 && b < 1 && c < 1)
				{
					if (ifLinearInterp)
					{
						CP3 temp = a * p0 + b * p1 + c * p2;
						if (temp.z < Zbuffer[GetIndex(i, j)])
						{
							Zbuffer[GetIndex(i, j)] = temp.z;
							CRGB coulor = a * p0.c + b * p1.c + c * p2.c;
							pDC->MoveTo(i, j);
							pDC->SetPixelV(i, j, RGB(abs(coulor.red * 255), abs(coulor.green * 255), abs(coulor.blue * 255)));
						}
					}
					else
					{
						CP3 temp = a * p0 + b * p1 + c * p2;
						if (temp.z < Zbuffer[GetIndex(i, j)])
						{
							Zbuffer[GetIndex(i, j)] = temp.z;
							pDC->MoveTo(i, j);
							pDC->SetPixelV(i, j, RGB(abs(F[iFace].coulor.red * 255), abs(F[iFace].coulor.green * 255), abs(F[iFace].coulor.blue * 255)));
						}
					}
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

					if (ifLinearInterp)
					{
						coulor[k].red = a * bP[F[iFace].Index[0]].c.red;
						coulor[k].green = b * bP[F[iFace].Index[1]].c.green;
						coulor[k].blue = c * bP[F[iFace].Index[2]].c.blue;
					}
				}
				if (a > 0 && b > 0 && c > 0 && a < 1 && b < 1 && c < 1)
				{
					if (ifLinearInterp)
					{
						CRGB COULOR = (coulor[0] + coulor[1] + coulor[2] + coulor[3]) / 4;
						pDC->MoveTo(i, j);
						pDC->SetPixelV(i, j, RGB(abs(COULOR.red * 255), abs(COULOR.green * 255), abs(COULOR.blue * 255)));
					}
					else
					{
						pDC->MoveTo(i, j);
						pDC->SetPixelV(i, j, RGB(abs(F[iFace].coulor.red * 255), abs(F[iFace].coulor.green * 255), abs(F[iFace].coulor.blue * 255)));
					}
				}
			}
		}
	}
}

void CCubeT::Rasterization(CDC* pDC, BOOL ifLinearInterp, BOOL SSAA, int iFace, double* Zbuffer, CP3 cameraPosition, CLighting lighting)
{
	//Phong
	int MAX_x = fmax(bP[F[iFace].Index[0]].x, fmax(bP[F[iFace].Index[1]].x, bP[F[iFace].Index[2]].x));
	int MAX_y = fmax(bP[F[iFace].Index[0]].y, fmax(bP[F[iFace].Index[1]].y, bP[F[iFace].Index[2]].y));
	int MIN_x = fmin(bP[F[iFace].Index[0]].x, fmin(bP[F[iFace].Index[1]].x, bP[F[iFace].Index[2]].x));
	int MIN_y = fmin(bP[F[iFace].Index[0]].y, fmin(bP[F[iFace].Index[1]].y, bP[F[iFace].Index[2]].y));
	CP3 p0 = bP[F[iFace].Index[0]];
	CP3 p1 = bP[F[iFace].Index[1]];
	CP3 p2 = bP[F[iFace].Index[2]];
	LoadPointNormal();//计算顶点法向量
	for (int i = MIN_x; i <= MAX_x; i++)
	{
		for (int j = MIN_y; j <= MAX_y; j++)
		{
			if (!SSAA)
			{
				double a = ((-(i - p1.x) * (p2.y - p1.y) + (j - p1.y) * (p2.x - p1.x)) /
					(-(p0.x - p1.x) * (p2.y - p1.y) + (p0.y - p1.y) * (p2.x - p1.x)));
				double b = ((-(i - p2.x) * (p0.y - p2.y) + (j - p2.y) * (p0.x - p2.x)) /
					(-(p1.x - p2.x) * (p0.y - p2.y) + (p1.y - p2.y) * (p0.x - p2.x)));
				double c = 1 - a - b;
				if (a > 0 && b > 0 && c > 0 && a < 1 && b < 1 && c < 1)
				{
					if (ifLinearInterp)
					{
						CP3 temp = a * p0 + b * p1 + c * p2;
						if (temp.z < Zbuffer[GetIndex(i, j)])
						{
							Zbuffer[GetIndex(i, j)] = temp.z;
							CRGB coulor(a * P[F[iFace].Index[0]].c.red, b * P[F[iFace].Index[1]].c.green, c * P[F[iFace].Index[2]].c.blue);
							pDC->MoveTo(i, j);
							pDC->SetPixelV(i, j, RGB(abs(coulor.red * 255), abs(coulor.green * 255), abs(coulor.blue * 255)));
						}
					}
					else
					{
						CP3 temp = a * p0 + b * p1 + c * p2;
						if (temp.z < Zbuffer[GetIndex(i, j)])
						{
							Zbuffer[GetIndex(i, j)] = temp.z;
							pDC->MoveTo(i, j);
							
							//Shader
							CRGB coulor = PhongShader(cameraPosition,lighting, a, b, c, iFace);
							coulor.red = coulor.red > 1 ? 1 : coulor.red;
							coulor.green = coulor.green > 1 ? 1 : coulor.green;
							coulor.blue = coulor.blue > 1 ? 1 : coulor.blue;
							pDC->SetPixelV(i, j, RGB((coulor.red * 255), (coulor.green * 255), (coulor.blue * 255)));
						}
					}
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

					if (ifLinearInterp)
					{
						coulor[k].red = a * bP[F[iFace].Index[0]].c.red;
						coulor[k].green = b * bP[F[iFace].Index[1]].c.green;
						coulor[k].blue = c * bP[F[iFace].Index[2]].c.blue;
					}
				}
				if (a > 0 && b > 0 && c > 0 && a < 1 && b < 1 && c < 1)
				{
					if (ifLinearInterp)
					{
						CRGB COULOR = (coulor[0] + coulor[1] + coulor[2] + coulor[3]) / 4;
						pDC->MoveTo(i, j);
						pDC->SetPixelV(i, j, RGB(abs(COULOR.red * 255), abs(COULOR.green * 255), abs(COULOR.blue * 255)));
					}
					else
					{
						pDC->MoveTo(i, j);
						pDC->SetPixelV(i, j, RGB(abs(F[iFace].coulor.red * 255), abs(F[iFace].coulor.green * 255), abs(F[iFace].coulor.blue * 255)));
					}
				}
			}
		}
	}
}

void CCubeT::Rasterization(CDC* pDC, int iFace, double* Zbuffer, CP3 CameraPosition, CLighting lighting)
{
	BOOL SSAA = FALSE;
	BOOL ifLinearInterp = FALSE;

	int MAX_x = fmax(bP[F[iFace].Index[0]].x, fmax(bP[F[iFace].Index[1]].x, bP[F[iFace].Index[2]].x));
	int MAX_y = fmax(bP[F[iFace].Index[0]].y, fmax(bP[F[iFace].Index[1]].y, bP[F[iFace].Index[2]].y));
	int MIN_x = fmin(bP[F[iFace].Index[0]].x, fmin(bP[F[iFace].Index[1]].x, bP[F[iFace].Index[2]].x));
	int MIN_y = fmin(bP[F[iFace].Index[0]].y, fmin(bP[F[iFace].Index[1]].y, bP[F[iFace].Index[2]].y));

	CP3 p0 = bP[F[iFace].Index[0]];
	CP3 p1 = bP[F[iFace].Index[1]];
	CP3 p2 = bP[F[iFace].Index[2]];

	for (int i = MIN_x; i <= MAX_x; i++)
	{
		for (int j = MIN_y; j <= MAX_y; j++)
		{
			if (!SSAA)
			{
				double a = ((-(i - p1.x) * (p2.y - p1.y) + (j - p1.y) * (p2.x - p1.x)) /
					(-(p0.x - p1.x) * (p2.y - p1.y) + (p0.y - p1.y) * (p2.x - p1.x)));
				double b = ((-(i - p2.x) * (p0.y - p2.y) + (j - p2.y) * (p0.x - p2.x)) /
					(-(p1.x - p2.x) * (p0.y - p2.y) + (p1.y - p2.y) * (p0.x - p2.x)));
				double c = 1 - a - b;
				if (a > 0 && b > 0 && c > 0 && a < 1 && b < 1 && c < 1)
				{
					if (ifLinearInterp)
					{
						CP3 temp = a * p0 + b * p1 + c * p2;
						if (temp.z < Zbuffer[GetIndex(i, j)])
						{
							Zbuffer[GetIndex(i, j)] = temp.z;
							CRGB coulor = a * p0.c + b * p1.c + c * p2.c;
							pDC->MoveTo(i, j);
							pDC->SetPixelV(i, j, RGB(abs(coulor.red * 255), abs(coulor.green * 255), abs(coulor.blue * 255)));
						}
					}
					else
					{
						CP3 temp = a * p0 + b * p1 + c * p2;
						if (temp.z < Zbuffer[GetIndex(i, j)])
						{
							Zbuffer[GetIndex(i, j)] = temp.z;
							pDC->MoveTo(i, j);
							pDC->SetPixelV(i, j, RGB(abs((temp.z / 10-100)/100 * 255), abs((temp.z / 10-100) / 100 * 255), abs((temp.z / 10-100) / 100 * 255)));
						}
					}
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

					if (ifLinearInterp)
					{
						coulor[k].red = a * bP[F[iFace].Index[0]].c.red;
						coulor[k].green = b * bP[F[iFace].Index[1]].c.green;
						coulor[k].blue = c * bP[F[iFace].Index[2]].c.blue;
					}
				}
				if (a > 0 && b > 0 && c > 0 && a < 1 && b < 1 && c < 1)
				{
					if (ifLinearInterp)
					{
						CRGB COULOR = (coulor[0] + coulor[1] + coulor[2] + coulor[3]) / 4;
						pDC->MoveTo(i, j);
						pDC->SetPixelV(i, j, RGB(abs(COULOR.red * 255), abs(COULOR.green * 255), abs(COULOR.blue * 255)));
					}
					else
					{
						pDC->MoveTo(i, j);
						pDC->SetPixelV(i, j, RGB(abs(F[iFace].coulor.red * 255), abs(F[iFace].coulor.green * 255), abs(F[iFace].coulor.blue * 255)));
					}
				}
			}
		}
	}
}

CRGB CCubeT::PhongShader(CP3 CameraPosition, CLighting lighting, double a, double b, double c, int iFace)
{
	CP3 point = P[F[iFace].Index[0]] * a + P[F[iFace].Index[1]] * b + P[F[iFace].Index[2]] * c;//获得点
	CP3 norm = nP[F[iFace].Index[0]] * a + nP[F[iFace].Index[1]] * b + nP[F[iFace].Index[2]] * c;//获得点法向量
	CRGB ans = material.Emission;
	for (int i = 0; i < lighting.LightNumber; i++)
	{
		CP3 light = (lighting.LightSRC[i].Position - point);	light.normalization();			//光线
		CP3 view = CameraPosition - point;						view.normalization();			//实现
		CP3 half = (light + view);								half.normalization();			//半程向量
		double r2 = lighting.LightSRC[i].c2 * (lighting.LightSRC->Position - point).GetLenth2()
			+ lighting.LightSRC[i].c1 * (lighting.LightSRC->Position - point).GetLenth()
			+ lighting.LightSRC[i].c0;															//距离
		
		auto Ld = material.DiffuseM * (lighting.LightSRC[i].DiffuseL / r2) * max(0, norm.Dot(light));
		auto Ls = material.SpecularM * (lighting.LightSRC[i].SpecularL / r2) * pow(max(0, norm.Dot(half)), material.n);
		auto La = material.AmbientM * lighting.AmbientL;
		ans = Ld + La + Ls;
	}
	return ans;
}

int CCubeT::GetIndex(int x, int y)//获得深度index
{
	return (y + 1000) * 600 + x + 2000;	//不是严格的哈希，但是在屏幕范围内适用
}

