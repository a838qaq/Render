#include "pch.h"
#include "Lighting.h"

CLighting::CLighting()
{
	LightSRC = NULL;
	LightNumber = 0;
	AmbientL = CRGB(0.3, 0.3, 0.3);
}

CLighting::~CLighting()
{
	if (!LightNumber)
	{
		delete[]LightSRC;
		LightSRC = NULL;
	}
}

void CLighting::SetAmbient(CRGB c)
{
	AmbientL = c;
}

void CLighting::SetLighting(int LightNumber)
{
	if (this->LightNumber)
	{
		delete[]LightSRC;
	}
	if (LightNumber <= 0)
	{
		exit(1);
		return;
	}
	LightSRC = new CLightSRC[LightNumber];
	this->LightNumber = LightNumber;
}
