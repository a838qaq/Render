#pragma once
#include "P3.h"

class CFace
{
public:
	CFace();
	virtual ~CFace();
	void SetIndex(int a, int b, int c, int d);

public:
	int Number;//������Ŀ
	int Index[4];//��������
};

