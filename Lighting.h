#pragma once
#include "LightSRC.h"
#include "RGB.h"

class CLighting
{
public:
	CLighting();
	virtual ~CLighting();
	void SetAmbient(CRGB c);
	void SetLighting(int LightNumber);

public:
	CRGB AmbientL;		//环境光
	int LightNumber;	//光源数量
	CLightSRC* LightSRC;//光源组
};

