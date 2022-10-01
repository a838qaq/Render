#pragma once
#include "P3.h"
#include "RGB.h"

class CLightSRC
{
public:
	void SetPosition(CP3 Position);
	void SetDiffuse(CRGB c);
	void SetSpecular(CRGB c);
	void SetFade(double c0, double c1, double c2);
	void SetLightON(BOOL ifOn);

public:
	CP3 Position;//光源位置
	CRGB DiffuseL;//漫反射光强
	CRGB SpecularL;//镜面反射光强
	double c0, c1, c2;//光线衰减系数
	BOOL ifOn;//光源是否打开
};

