#pragma once

#include <easyx.h>
#include "../Config/Config.h"

class CStone : public CGod
{
public:
	IMAGE m_Stone;

public:
	CStone();
	~CStone();
	void InitStone(int x, int y);
	void ShowStone();
};