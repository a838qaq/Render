#include "pch.h"
#include "LightSRC.h"

void CLightSRC::SetPosition(CP3 Position)
{
	this->Position = Position;
}

void CLightSRC::SetDiffuse(CRGB c)
{
	this->DiffuseL = c;
}

void CLightSRC::SetSpecular(CRGB c)
{
	SpecularL = c;
}

void CLightSRC::SetFade(double c0, double c1, double c2)
{
	this->c0 = c0;
	this->c1 = c1;
	this->c2 = c2;
}

void CLightSRC::SetLightON(BOOL ifOn)
{
	this->ifOn = ifOn;
}
