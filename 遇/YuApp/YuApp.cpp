#include "YuApp.h"
#include "../Config/Config.h"

CREATE_OBJECT(CYuApp)
WINDOW_PARAM(520 + 16, 520 + 39, 40, 20, L"遇")

CYuApp::CYuApp()
{

}

CYuApp::~CYuApp()
{

}

void CYuApp::Init()
{
	// 初始化背景
	m_Back.InitBack();

	// 初始化玩家
	m_Player.InitPlayer();

	// 设定所有定时器
	SetTimer();

	// 生成野生朋友
	m_FriendBox.CreateFriend(3);
}

void CYuApp::Paint()
{
	// 显示背景
	m_Back.ShowBack();

	// 显示玩家
	m_Player.ShowPlayer();

	// 显示玩家的朋友
	m_Player.ShowAllFriend();

	// 显示所有野生朋友
	m_FriendBox.ShowAll();
}

void CYuApp::Close(WPARAM& w, LPARAM& l)
{

}

void CYuApp::ON_WM_KEYDOWN(WPARAM& key)
{
	if (key == VK_UP || key == VK_DOWN || key == VK_LEFT || key == VK_RIGHT) { // 如果按方向键
		m_Player.MovePlayer(key, PLAYER_MOVE_STEP);
	}
	else if (key == 'F') {
		m_Player.GetFriend(m_FriendBox.Friending(m_Player));
	}
}

void CYuApp::SetTimer()
{
	::SetTimer(m_hWnd, CHECK_BLOCK_TIMEID, CHECH_BLOCK_INTERVAL, nullptr);
}

void CYuApp::ON_WM_TIMER(WPARAM& w, LPARAM& l)
{
	switch (w) {
	case CHECK_BLOCK_TIMEID: {
		CheckBlock();
	}
	}
}

// 刷新所有方块的占有情况
void CYuApp::CheckBlock()
{
	for (int i = 0; i < 13; ++i) for (int j = 0; j < 13; ++j) mp[i][j] = 0;
	m_Player.Check();
	m_FriendBox.Check();
}