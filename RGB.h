#pragma once
class CRGB
{
public:
	CRGB(void);
	CRGB(double red, double green, double blue, double alpha = 0.0);
	virtual ~CRGB(void);

	void SetRGB(double red, double green, double blue);
	void SetRGB(double red, double green, double blue, double alpha);
	void Normalize();

	friend CRGB operator + (const CRGB &c0, const CRGB& c1);
	friend CRGB operator - (const CRGB &c0, const CRGB& c1);
	friend CRGB operator * (const CRGB &c0, double scalar);
	friend CRGB operator * (double scalar, const CRGB &c0);
	friend CRGB operator / (const CRGB& p, double scalao);
	friend CRGB operator * (const CRGB& c0, const CRGB& c1);

public:
	double red;
	double green;
	double blue;
	double alpha;
};

