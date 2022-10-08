#pragma once
#include "P3.h"
#include "FaceT.h"
#include "Lighting.h"
#include "Material.h"
#include "Lighting.h"
#include "CubeT.h"

class CCoordinate
{
public:
	CCoordinate();
	virtual ~CCoordinate();
	CP3* GetPoint();//获取顶点表
	void Draw(CDC* pDC, double* Zbuffer, CP3 CameraPosition, CLighting lighting, int nHeight, int nWidth);//绘制
	void LoadBufferPoint();//读入缓存
	CP3* GetBufferPoint();//获取缓存顶点表
	void Rasterization(CDC* pDC, BOOL ifLinearInterp, BOOL SSAA, int iFace, double* Zbuffer, int nHeight, int nWidth, CP3 CameraPosition, CLighting lighting);//光栅化三角形
	void Rasterization(CDC* pDC, BOOL ifLinearInterp, BOOL SSAA, int iFace, double* Zbuffer, int nHeight, int nWidth,int depth);//深度图
	CRGB PhongShader(CP3 CameraPosition, CLighting lighting, double a, double b, double c, int iFace);//PhongShaer 计算着色
	BOOL ifLighting(CCubeT cube, CCoordinate coordinate, CP3 CameraPosition, CLighting lighting, double a, double b, double c, int iFace);
	BOOL ifLightingUnderCube(CCubeT cube, CP3 CameraPosition, CLighting lighting, double a, double b, double c, int iFace);

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
	CMaterial material;

	CPoint2 MSAA[4];		//2 x SSAA
};

