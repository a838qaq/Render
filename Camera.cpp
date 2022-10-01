#include "pch.h"
#include "Camera.h"


CCamera::CCamera()
{
	ZbufferMax = 5000000;
	for (int i = 0; i < ZbufferMax; i++)
	{
		Zbuffer[i] = 999999999;
	}
}

void CCamera::SetPosition(double x, double y, double z)
{
	Position.getXYZ(x, y, z);
}

void CCamera::SetDirector(double x, double y, double z)
{
	Director.getXYZ(x, y, z);
	Director.normalization();
}

void CCamera::SetHead(double x, double y, double z)
{
	Head.getXYZ(x, y, z);
	Head.normalization();
}

void CCamera::SetN(double n)
{
	this->n = n;
}

void CCamera::SetF(double f)
{
	this->f = f;
}

CP3* CCamera::GetPositonPoint()
{
	return &Position;
}

CP3* CCamera::GetDirectorPoint()
{
	return &Director;
}

CP3* CCamera::GetHeadPoint()
{
	return &Head;
}

double* CCamera::GetZbuffer()
{
	return Zbuffer;
}

int CCamera::GetZbufferMax()
{
	return ZbufferMax;
}

void CCamera::InitZbuffer()
{
	for (int i = 0; i < ZbufferMax; i++)
	{
		Zbuffer[i]= 999999999;
	}
}

void CCamera::MoreWide()
{
	n += 100;
}

void CCamera::MoreNarrow()
{
	n -= 100;
}
