#include "pch.h"
#include "Material.h"

CMaterial::CMaterial()
{
}

CMaterial::~CMaterial()
{
}

void CMaterial::SetAmbient(CRGB c)
{
	AmbientM = c;
}

void CMaterial::SetDiffuse(CRGB c)
{
	DiffuseM = c;
}

void CMaterial::SetSpecular(CRGB c)
{
	SpecularM = c;
}

void CMaterial::SetEmission(CRGB c)
{
	Emission = c;
}

void CMaterial::SetHightLight(double n)
{
	this->n = n;
}
