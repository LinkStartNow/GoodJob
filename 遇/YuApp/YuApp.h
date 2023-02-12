#pragma once

#include "../GameFrame/GameFrame.h"
#include "../BackGround/BackGround.h"
#include "../Player/Player.h"
#include "../FriendBox/FriendBox.h"

class CYuApp : public CGameFrame
{
public:
	CBackGround m_Back;
	CPlayer m_Player;
	CFriendBox m_FriendBox;

public:
	CYuApp();
	~CYuApp();
	virtual void Init();
	virtual void Paint();
	virtual void Close(WPARAM& w, LPARAM& l);
	virtual void ON_WM_KEYDOWN(WPARAM& key);
	virtual void ON_WM_TIMER(WPARAM& w, LPARAM& l);
	void SetTimer();
	void CheckBlock();
};