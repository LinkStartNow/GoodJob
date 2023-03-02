#pragma once

#include <easyx.h>
#include <list>

using namespace std;

#include "../FriendBox/Friend.h"

class CPlayer : public CGod
{
public:
	IMAGE m_Player;
	IMAGE m_Mask;
	list<CFriend*> m_FriendList;
	bool Is_Help;

public:
	CPlayer();
	~CPlayer();
	void InitPlayer();
	void ShowPlayer();
	void MovePlayer(int direct, int step);
	void ShowAllFriend();
	void Check();
	void GetFriend(CFriend* f);
	void InitFriend();
};