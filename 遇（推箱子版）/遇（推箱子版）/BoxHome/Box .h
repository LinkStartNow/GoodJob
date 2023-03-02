#pragma once

#include <easyx.h>
#include "../Config/Config.h"

class CBox : public CGod
{
public:
	IMAGE m_Box;
	IMAGE m_BoxYes;

public:
	CBox();
	~CBox();
	void InitBox(int x, int y);
	void ShowBox();
};