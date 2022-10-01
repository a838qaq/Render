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
	CRGB AmbientL;		//������
	int LightNumber;	//��Դ����
	CLightSRC* LightSRC;//��Դ��
};

