#pragma once
#include "P3.h"
#include "FaceT.h"
#include "Material.h"
#include "Lighting.h"

class CCubeT
{
public:
	CCubeT(void);
	virtual ~CCubeT();

	void Init();//初始化
	void ReadFace();//读入面表
	void ReadPoint();//读入点表
	CP3* GetPoints();//获取顶点表
	CP3 GetCenterPoint();//获取中心坐标
	void LoadBuffer();//读入缓存
	void LoadPointNormal();//计算点法向量
	CP3* GetBufferPoint();//获取缓存顶点表
	void DeletFace(CP3 CameraPosition, int flag);//背面剔除
	void LoadFaceS();//计算每个面的面积

	void SetModeLineFrame();//设置绘制线框
	void SetModeFace();//设置绘制面
	void SetModeTriangle();//设置绘制三角形
	void SetModePhong();//设置Phong渲染
	void SetModeRGBBB();//设置颜色混合渲染

	void SetFaceRGB();//设置面的RGB
	void SetTriangleRGB();//设置三角形的RGB
	void SetPointRGB();//设置当前顶点的RGB
	int GetMode();//获取当前展现模式
	
	void Draw(CDC* pDC, double* Zbuffer, CP3 CameraPosition, CLighting lighting);//绘制图像
	void Rasterization(CDC* pDC, BOOL ifLinearInterp, BOOL SSAA, int iFace, double* Zbuffer);//光栅化三角形
	void Rasterization(CDC* pDC, BOOL ifLinearInterp, BOOL SSAA, int iFace, double* Zbuffer, CP3 CameraPosition, CLighting lighting);//带光照的光栅化
	CRGB PhongShader(CP3 CameraPosition, CLighting lighting, double a, double b, double c, int iFace);//PhongShaer 计算着色


	int GetIndex(int x, int y);//获取Zbuffer索引


public:
	CP3 P[8+12];			//点表
	CFaceT F[12];			//面表

	CP3 bP[8+12];			//点缓存，用于进行VP变换
	CP3 nP[8];				//点法向量，用于计算光照

	int VisionableFace[12];	//可视面

	int PNumber;			//点数
	int FNumber;			//面数
	int DrawMode;			//绘制模式

	BOOL SSAA;				//是否开启SSAA
	CPoint2 MSAA[4];		//2 x SSAA

	CMaterial material;		//材质	
};

