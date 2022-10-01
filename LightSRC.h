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
	CP3 Position;//��Դλ��
	CRGB DiffuseL;//�������ǿ
	CRGB SpecularL;//���淴���ǿ
	double c0, c1, c2;//����˥��ϵ��
	BOOL ifOn;//��Դ�Ƿ��
};

