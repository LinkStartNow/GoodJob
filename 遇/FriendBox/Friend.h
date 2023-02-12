#pragma once

#include <easyx.h>

class CFriend
{
public:
	IMAGE m_Friend;
	IMAGE m_Mask;
	int m_x;
	int m_y;

public:
	CFriend();
	~CFriend();
	void InitFriend(int x, int y);
	void ShowFrined();
};