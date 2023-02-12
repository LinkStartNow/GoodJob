#include "YuApp.h"
#include "../Config/Config.h"

CREATE_OBJECT(CYuApp)
WINDOW_PARAM(520 + 16, 520 + 39, 40, 20, L"��")

CYuApp::CYuApp()
{

}

CYuApp::~CYuApp()
{

}

void CYuApp::Init()
{
	// ��ʼ������
	m_Back.InitBack();

	// ��ʼ�����
	m_Player.InitPlayer();

	// �趨���ж�ʱ��
	SetTimer();

	// ����Ұ������
	m_FriendBox.CreateFriend(3);
}

void CYuApp::Paint()
{
	// ��ʾ����
	m_Back.ShowBack();

	// ��ʾ���
	m_Player.ShowPlayer();

	// ��ʾ��ҵ�����
	m_Player.ShowAllFriend();

	// ��ʾ����Ұ������
	m_FriendBox.ShowAll();
}

void CYuApp::Close(WPARAM& w, LPARAM& l)
{

}

void CYuApp::ON_WM_KEYDOWN(WPARAM& key)
{
	if (key == VK_UP || key == VK_DOWN || key == VK_LEFT || key == VK_RIGHT) { // ����������
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

// ˢ�����з����ռ�����
void CYuApp::CheckBlock()
{
	for (int i = 0; i < 13; ++i) for (int j = 0; j < 13; ++j) mp[i][j] = 0;
	m_Player.Check();
	m_FriendBox.Check();
}