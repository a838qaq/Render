#pragma once
#include "RGB.h"

class CMaterial
{
public:
	CMaterial();
	virtual ~CMaterial();

	void SetAmbient(CRGB c);
	void SetDiffuse(CRGB c);
	void SetSpecular(CRGB c);
	void SetEmission(CRGB c);
	void SetHightLight(double n);

public:
	CRGB AmbientM;	//环境光反射率
	CRGB DiffuseM;	//漫反射反射率
	CRGB SpecularM;	//镜面反射
	CRGB Emission;	//自身颜色
	double n;		//高光指数
};

