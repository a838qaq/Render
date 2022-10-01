#include "pch.h"
#include "RGB.h"

CRGB::CRGB(void)
{
	this->red = 0;
	this->green = 0;
	this->blue = 0;
	this->alpha = 0;
}

CRGB::CRGB(double red, double green, double blue, double alpha)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}

CRGB::~CRGB(void)
{
}

void CRGB::SetRGB(double red, double green, double blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

void CRGB::SetRGB(double red, double green, double blue, double alpha)
{
	SetRGB(red, green, blue);
	this->alpha = alpha;
}

void CRGB::Normalize()
{
	auto temp = *this;
	red = temp.red / (temp.red + temp.green + temp.blue);
	green= temp.green / (temp.red + temp.green + temp.blue);
	blue = temp.blue / (temp.red + temp.green + temp.blue);

}

CRGB operator+(const CRGB &c0, const CRGB &c1)
{
	CRGB New((c0.red + c1.red), (c0.green + c1.green), (c0.blue + c1.blue), (c0.alpha + c1.alpha));
	return New;
}

CRGB operator-(const CRGB &c0, const CRGB& c1)
{
	CRGB New((c0.red - c1.red), (c0.green - c1.green), (c0.blue - c1.blue), (c0.alpha - c1.alpha));
	return New;
}

CRGB operator*(const CRGB &c0, double scalar)
{
	CRGB New(c0.red * scalar, c0.green * scalar, c0.blue * scalar, c0.alpha);
	return New;
}

CRGB operator*(double scalar, const CRGB& c0)
{
	CRGB New(c0.red * scalar, c0.green * scalar, c0.blue * scalar, c0.alpha);
	return New;
}

CRGB operator/(const CRGB& p, double scalao)
{
	return CRGB(p.red / scalao, p.green / scalao, p.blue / scalao);
}

CRGB operator*(const CRGB& c0, const CRGB& c1)
{
	return CRGB(c0.red * c1.red, c0.green * c1.green, c0.blue * c1.blue);
}
