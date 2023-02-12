#pragma once

#include <easyx.h>
#include <list>

using namespace std;

#include "../FriendBox/Friend.h"

class CPlayer
{
public:
	IMAGE m_Player;
	IMAGE m_Mask;
	int m_x;
	int m_y;
	list<CFriend*> m_FriendList;

public:
	CPlayer();
	~CPlayer();
	void InitPlayer();
	void ShowPlayer();
	void MovePlayer(int direct, int step);
	void ShowAllFriend();
	void Check();
	void GetFriend(CFriend* f);
};