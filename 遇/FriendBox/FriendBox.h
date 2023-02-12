#pragma once

#include "Friend.h"
#include "../Player/Player.h"

#include <list>

using namespace std;

class CFriendBox
{
public:
	list<CFriend*> m_FriendBoxList;

public:
	CFriendBox();
	~CFriendBox();
	void ShowAll();
	void CreateFriend(int num);
	void Check();
	CFriend* Friending(CPlayer& player);
};