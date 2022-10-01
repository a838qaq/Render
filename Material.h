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
	CRGB AmbientM;	//�����ⷴ����
	CRGB DiffuseM;	//�����䷴����
	CRGB SpecularM;	//���淴��
	CRGB Emission;	//������ɫ
	double n;		//�߹�ָ��
};

