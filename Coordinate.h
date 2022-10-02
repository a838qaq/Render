#pragma once
#include "P3.h"
#include "FaceT.h"
#include "Lighting.h"

class CCoordinate
{
public:
	CCoordinate();
	virtual ~CCoordinate();
	CP3* GetPoint();//获取顶点表
	void Draw(CDC* pDC, double* Zbuffer, CP3 CameraPosition, CLighting lighting, int nHeight, int nWidth);//绘制
	void LoadBufferPoint();//读入缓存
	CP3* GetBufferPoint();//获取缓存顶点表
	void Rasterization(CDC* pDC, BOOL ifLinearInterp, BOOL SSAA, int iFace, double* Zbuffer, int nHeight, int nWidth);//光栅化三角形
	void Rasterization(CDC* pDC, BOOL ifLinearInterp, BOOL SSAA, int iFace, double* Zbuffer, int nHeight, int nWidth,int depth);//深度图

	int GetDrawMode();
	void SetDrawModeLine();
	void SetDrawModeColor();
	void SetDrawModeDepth();

	int GetIndex(int x, int y);//获取Zbuffer索引

public:
	CP3 P[19+24];
	int PNumber;
	CFaceT F[24];
	int FNumber;

	CP3 bP[19+24];
	int DrawMode;

	BOOL Axis[3];

	CPoint2 MSAA[4];		//2 x SSAA
};

