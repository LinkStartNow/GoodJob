#pragma once

#include "../GameFrame/GameFrame.h"
#include "../BackGround/BackGround.h"
#include "../Player/Player.h"
#include "../FriendBox/FriendBox.h"
#include "../BoxHome/BoxHome.h"
#include "../TargetBox/TargetBox.h"
#include "../StoneBox/StoneBox.h"

class CYuApp : public CGameFrame
{
public:
	CBackGround m_Back;
	CPlayer m_Player;
	CFriendBox m_FriendBox;
	CBoxHome m_BoxHome;
	CTargetBox m_TargetBox;
	CStoneBox m_StoneBox;
	int m_level;

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
	void GameOver();
	void NextStep();
	void Win();
	void ReStart();
};