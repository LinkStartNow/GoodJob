#pragma once

#include <easyx.h>

#include "../Config/Config.h"

class CFriend : public CGod
{
public:
	IMAGE m_Friend;
	IMAGE m_Mask;

public:
	CFriend();
	~CFriend();
	void InitFriend(int x, int y);
	void ShowFrined();
};