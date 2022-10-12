#include "pch.h"
#include "Coordinate.h"

CCoordinate::CCoordinate()
{
	Axis[0] = FALSE;
	Axis[1] = FALSE;
	Axis[2] = TRUE;

	MSAA[0].getXY(0.25, 0.25);
	MSAA[1].getXY(0.25, 0.75);
	MSAA[2].getXY(0.75, 0.25);
	MSAA[3].getXY(0.75, 0.75);
	DrawMode = 0;
	P[0].getXYZ(0, 0, 0);
	P[1].getXY(200, 0.0);
	P[2].getXYZ(0, 200, 0);
	P[3].getXYZ(-200, 0, 0);
	P[4].getXYZ(0, -200, 0);
	P[5].getXYZ(0, 0, 200);
	P[6].getXYZ(0, 0, -200);
	P[7].getXYZ(200, 200, 0);
	P[8].getXYZ(-200, 200, 0);
	P[9].getXYZ(-200, -200, 0);
	P[10].getXYZ(200, -200, 0);
	P[11].getXYZ(-200, 0, 200);
	P[12].getXYZ(200, 0, 200);
	P[13].getXYZ(200, 0, -200);
	P[14].getXYZ(-200, 0, -200);
	P[15].getXYZ(0, -200, 200);
	P[16].getXYZ(0, 200, 200);
	P[17].getXYZ(0, -200, -200);
	P[18].getXYZ(0, 200, -200);
	F[0].SetIndex(0, 1, 7);
	F[1].SetIndex(0, 2, 7); 
	F[2].SetIndex(0, 2, 8);
	F[3].SetIndex(0, 3, 8);
	F[4].SetIndex(0, 4, 9);
	F[5].SetIndex(0, 3, 9); 
	F[6].SetIndex(0, 4, 10);
	F[7].SetIndex(0, 1, 10);
	for (int i = 0; i < 8; i++)
	{
		F[i].SetNormal(0, 0, 1);
		F[i].SetRGB(0.5, 0, 0.5);
	}

	F[8].SetIndex(0, 6, 18);
	F[9].SetIndex(0, 2, 18);
	F[10].SetIndex(0, 2, 16);
	F[11].SetIndex(0, 5, 16);
	F[12].SetIndex(0, 5, 15);
	F[13].SetIndex(0, 4, 15);
	F[14].SetIndex(0, 4, 17);
	F[15].SetIndex(0, 6, 17);
	for (int i = 8; i < 16; i++)
	{
		F[i].SetNormal(1, 0, 0);
		F[i].SetRGB(0.5, 0.5, 0);
	}
	
	F[16].SetIndex(0, 1, 13);
	F[17].SetIndex(0, 6, 13);
	F[18].SetIndex(0, 6, 14);
	F[19].SetIndex(0, 3, 14);
	F[20].SetIndex(0, 3, 11);
	F[21].SetIndex(0, 5, 11);
	F[22].SetIndex(0, 5, 12);
	F[23].SetIndex(0, 1, 12);
	for (int i = 16; i < 24; i++)
	{
		F[i].SetNormal(0, 1, 0);
		F[i].SetRGB(0, 0.5, 0.5);
	}

	PNumber = 43;//
	FNumber = 24;
}

CCoordinate::~CCoordinate()
{
}

CP3* CCoordinate::GetPoint()
{
	return P;
}

void CCoordinate::Draw(CDC* pDC, double* Zbuffer, CP3 CameraPosition, CLighting lighting, int nHeight, int nWidth, CCubeT cube)
{
	if (DrawMode == 0)
	{
		CPoint2 ScreemPoint, temp;
		int LastIndex = 0;
		if (Axis[2])
		{
			for (int iFace = 0; iFace < FNumber / 3; iFace++)
			{
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
						pDC->LineTo((int)ScreemPoint.x, (int)ScreemPoint.y);
						LastIndex = F[iFace].Index[iPoint];
					}
				}
				pDC->LineTo(temp.x, temp.y);
			}
		}
		if (Axis[0])
		{
			for (int iFace = FNumber / 3; iFace < FNumber * 2 / 3; iFace++)
			{
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
						pDC->LineTo((int)ScreemPoint.x, (int)ScreemPoint.y);
						LastIndex = F[iFace].Index[iPoint];
					}
				}
				pDC->LineTo(temp.x, temp.y);
			}
		}
		if (Axis[1])
		{
			for (int iFace = FNumber * 2 / 3; iFace < FNumber; iFace++)
			{
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
						pDC->LineTo((int)ScreemPoint.x, (int)ScreemPoint.y);
						LastIndex = F[iFace].Index[iPoint];
					}
				}
				pDC->LineTo(temp.x, temp.y);
			}
		}
	}
	else if (DrawMode == 1)
	{
		if (Axis[2])
		{
			for (int iFace = 0; iFace < FNumber/3; iFace++)
			{
				Rasterization(pDC, FALSE, FALSE, iFace, Zbuffer, nHeight, nWidth, CameraPosition, lighting, cube);
			}
		}
		if (Axis[0])
		{
			for (int iFace = FNumber/3; iFace < FNumber*2/3; iFace++)
			{
				Rasterization(pDC, FALSE, FALSE, iFace, Zbuffer, nHeight, nWidth, CameraPosition, lighting, cube);
			}
		}
		if (Axis[1])
		{
			for (int iFace = FNumber*2/3; iFace < FNumber; iFace++)
			{
				Rasterization(pDC, FALSE, FALSE, iFace, Zbuffer, nHeight, nWidth, CameraPosition, lighting, cube);
			}
		}
	}
	else if (DrawMode == 2)
	{
		if (Axis[2])
		{
			for (int iFace = 0; iFace < FNumber / 3; iFace++)
			{
				Rasterization(pDC, FALSE, FALSE, iFace, Zbuffer, nHeight, nWidth, 1);
			}
		}
		if (Axis[0])
		{
			for (int iFace = FNumber / 3; iFace < FNumber * 2 / 3; iFace++)
			{
				Rasterization(pDC, FALSE, FALSE, iFace, Zbuffer, nHeight, nWidth, 1);
			}
		}
		if (Axis[1])
		{
			for (int iFace = FNumber * 2 / 3; iFace < FNumber; iFace++)
			{
				Rasterization(pDC, FALSE, FALSE, iFace, Zbuffer, nHeight, nWidth ,1);
			}
		}
	}
}

void CCoordinate::LoadBufferPoint()
{
	for (int i = 0; i < PNumber; i++)
	{
		bP[i] = P[i];
	}
}

CP3* CCoordinate::GetBufferPoint()
{
	return bP;
}

void CCoordinate::Rasterization(CDC* pDC, BOOL ifLinearInterp, BOOL SSAA, int iFace, double* Zbuffer, int nHeight, int nWidth, CP3 cameraPosition, CLighting lighting, CCubeT cube)
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
			if (i < -nWidth || i > nWidth) continue;
			if (j < -nHeight || j > nHeight) continue;

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

							//Shader
							CRGB coulor = PhongShader(cameraPosition, lighting, a, b, c, iFace, cube);
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

void CCoordinate::Rasterization(CDC* pDC, BOOL ifLinearInterp, BOOL SSAA, int iFace, double* Zbuffer, int nHeight, int nWidth, int depth)
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
			if (i < -nWidth || i > nWidth) continue;
			if (j < -nHeight || j > nHeight) continue;
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
							pDC->SetPixelV(i, j, RGB(abs((temp.z / 10 - 100) / 100 * 255), abs((temp.z / 10 - 100) / 100 * 255), abs((temp.z / 10 - 100) / 100 * 255)));
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

CRGB CCoordinate::PhongShader(CP3 CameraPosition, CLighting lighting, double a, double b, double c, int iFace, CCubeT cube)
{
	CP3 point = P[F[iFace].Index[0]] * a + P[F[iFace].Index[1]] * b + P[F[iFace].Index[2]] * c;//获得点
	CP3 norm = F[iFace].Normal;//获得点法向量
	CRGB ans = material.Emission;
	for (int i = 0; i < lighting.LightNumber; i++)
	{
		CRGB Ld, Ls, La;
		if (ifLighting(cube, *this, CameraPosition, lighting, a, b, c, iFace, i))
		{
			CP3 light = (lighting.LightSRC[i].Position - point);	light.normalization();			//光线
			CP3 view = CameraPosition - point;						view.normalization();			//实现
			CP3 half = (light + view);								half.normalization();			//半程向量
			double r2 = lighting.LightSRC[i].c2 * (lighting.LightSRC->Position - point).GetLenth2()
				+ lighting.LightSRC[i].c1 * (lighting.LightSRC->Position - point).GetLenth()
				+ lighting.LightSRC[i].c0; 			
			Ld = material.DiffuseM * (lighting.LightSRC[i].DiffuseL / r2) * max(0, norm.Dot(light));
			Ls = material.SpecularM * (lighting.LightSRC[i].SpecularL / r2) * pow(max(0, norm.Dot(half)), material.n);
		}
		else
		{
			Ld.SetRGB(0, 0, 0);
			Ls.SetRGB(0, 0, 0); 
		}
		La = material.AmbientM * lighting.AmbientL;
		ans = ans + Ld + La + Ls;
	}
	return ans;
}

BOOL CCoordinate::ifLighting(CCubeT cube, CCoordinate coordinate, CP3 CameraPosition, CLighting lighting, double a, double b, double c, int iFace, int iLight)
{
	return (ifLightingUnderCube(cube, CameraPosition, lighting, a, b, c, iFace, iLight));
}

BOOL CCoordinate::ifLightingUnderCube(CCubeT cube, CP3 CameraPosition, CLighting lighting, double a, double b, double c, int iFace, int iLight)
{
	CP3 E1, E2, S, S1, S2, O = P[F[iFace].Index[0]] * a + P[F[iFace].Index[1]] * b + P[F[iFace].Index[2]] * c;
	CP3 D = lighting.LightSRC[iLight].Position - O;
	D.normalization();
	double b1, b2;
	for (int iFace = 2; iFace <3; iFace++)
	{
		E1 = cube.P[F[iFace].Index[1]] - cube.P[F[iFace].Index[0]];
		E2 = cube.P[F[iFace].Index[2]] - cube.P[F[iFace].Index[0]];
		S = O - cube.P[F[iFace].Index[0]];
		S1 = D.Cross(E2);
		S2 = S.Cross(E1);
		double temp = (S1.Dot(E1));
		b1 = S1.Dot(S) / temp;
		b2 = S2.Dot(D) / temp;
		
		if (b1 >= 0 && b2 >= 0 && (1 - b1 - b2) >= 0)
		{
			return FALSE;
		}
	}
	return TRUE;
}

int CCoordinate::GetDrawMode()
{
	return DrawMode;
}

void CCoordinate::SetDrawModeLine()
{
	DrawMode = 0;
}

void CCoordinate::SetDrawModeColor()
{
	DrawMode = 1;
}

void CCoordinate::SetDrawModeDepth()
{
	DrawMode = 2;
}

int CCoordinate::GetIndex(int x, int y)
{
	return (y + 1000) * 600 + x + 2000;
}
