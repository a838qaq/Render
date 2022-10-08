#pragma once
#include "P3.h"

class CCamera
{
public:
	CCamera();
	void SetPosition(double x, double y, double z);
	void SetDirector(double x, double y, double z);
	void SetHead(double x, double y, double z);
	void SetN(double n);
	void SetF(double f);

	CP3* GetPositonPoint();
	CP3* GetDirectorPoint();
	CP3* GetHeadPoint();
	double* GetZbuffer();
	int GetZbufferMax();
	void InitZbuffer();
	void MoreWide();
	void MoreNarrow();

public:
	CP3 Position;//摄像机位置
	CP3 Director;//摄像机的指向
	CP3 Head;//摄像机的头顶方向
	double n;//投影近平面
	double f;//可视远平面
	double Zbuffer[5000000];//Zbuffer
	int ZbufferMax;//Zbuffer最大值
};

