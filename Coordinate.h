#pragma once
#include "P3.h"
#include "FaceT.h"
#include "Lighting.h"

class CCoordinate
{
public:
	CCoordinate();
	virtual ~CCoordinate();
	CP3* GetPoint();//��ȡ�����
	void Draw(CDC* pDC, double* Zbuffer, CP3 CameraPosition, CLighting lighting, int nHeight, int nWidth);//����
	void LoadBufferPoint();//���뻺��
	CP3* GetBufferPoint();//��ȡ���涥���
	void Rasterization(CDC* pDC, BOOL ifLinearInterp, BOOL SSAA, int iFace, double* Zbuffer, int nHeight, int nWidth);//��դ��������
	void Rasterization(CDC* pDC, BOOL ifLinearInterp, BOOL SSAA, int iFace, double* Zbuffer, int nHeight, int nWidth,int depth);//���ͼ

	int GetDrawMode();
	void SetDrawModeLine();
	void SetDrawModeColor();
	void SetDrawModeDepth();

	int GetIndex(int x, int y);//��ȡZbuffer����

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

