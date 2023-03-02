#pragma once

#include <easyx.h>

class CTarget
{
public:
	IMAGE m_Target;
	int m_x;
	int m_y;

public:
	CTarget();
	~CTarget();
	void InitTarget(int x, int y);
	void ShowTarget();
};