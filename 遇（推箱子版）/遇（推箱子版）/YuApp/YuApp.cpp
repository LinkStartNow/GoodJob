#include "YuApp.h"
#include "../Config/Config.h"

CREATE_OBJECT(CYuApp)
WINDOW_PARAM(520 + 16, 520 + 39, 40, 20, L"��")

CYuApp::CYuApp() : m_level(0)
{

}

CYuApp::~CYuApp()
{

}

void CYuApp::Init()
{
	// ��ʼ����һ��
	m_level = 1;

	// ��ʼ������
	m_Back.InitBack();

	// ��ʼ�����
	m_Player.InitPlayer();

	// �趨���ж�ʱ��
	SetTimer();

	// ��������
	m_BoxHome.CreateBox(m_level);

	// ��һ�ؾͲ���������
	//// ����Ұ������
	//m_FriendBox.CreateFriend(m_level);

	// ����Ŀ�ĵ�
	m_TargetBox.CreateTarget(m_level);

	// ����ʯͷ
	m_StoneBox.CreateStone(m_level * 2);
}

void CYuApp::Paint()
{
	// ��ʾ����
	m_Back.ShowBack();

	// ��ʾĿ�ĵ�
	m_TargetBox.ShowAll();

	// ��ʾ���
	m_Player.ShowPlayer();

	// ��ʾ��ҵ�����
	m_Player.ShowAllFriend();

	// ��ʾ��������
	m_BoxHome.ShowAll();

	// ��ʾ����Ұ������
	m_FriendBox.ShowAll();

	// ��ʾ����ʯͷ
	m_StoneBox.ShowAll();
}

void CYuApp::Close(WPARAM& w, LPARAM& l)
{

}

void CYuApp::ON_WM_KEYDOWN(WPARAM& key)
{
	static int help = 0;

	if (key == VK_UP || key == VK_DOWN || key == VK_LEFT || key == VK_RIGHT) { // ����������
		m_Player.MovePlayer(key, PLAYER_MOVE_STEP);
	}
	else if (key == 'F') { // �û���f��
		m_Player.GetFriend(m_FriendBox.Friending(m_Player));
	}
	else if (key == VK_SPACE) { // �û��˿ո�
		::MessageBox(m_hWnd, L"�����ڷ����������ǰܸ������˰ɣ������������鳰Ц��", L"23333���Ц", MB_OK);
		GameOver();
	}
	else if (key == 'H') {
		help = 1;
	}
	else if (key == 'E') {
		help = help == 1 ? 2 : 0;
	}
	else if (key == 'L') {
		help = help == 2 ? 3 : 0;
	}
	else if (key == 'P') {
		if (help == 3) { // �Ѿ����������� h e l
			if (m_Player.Is_Help) { // �Ѿ�ʹ�ù����������ٰ���
				help = 0;
				::MessageBox(m_hWnd, L"���Ѿ����ܹ�һ�ΰ����ˣ�ʣ�µĿ��Լ��ɣ�", L"��ʾ", MB_OK);
			}
			else { // ����������ֱ�Ӵ������һ������
				m_Player.Is_Help = 1;
				CFriend* f = new CFriend;
				f->InitFriend(m_Player.m_x, m_Player.m_y);
				m_Player.m_FriendList.push_back(f);
			}
		}
	}
	// �ۼ�����
	else if (key == 'G') { 
		m_Player.InitFriend();
	}

	// ���õ�ǰ�ؿ�
	else if (key == 'R') {
		ReStart();
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
		if (!res) { // ����ȫ��������ȷλ�ã�������һ��
			NextStep();
			::MessageBox(m_hWnd, L"��ϲ���ɹ�������һ�أ�", L"��ʾ", MB_OK);
			//GameOver();
			return;
		}
	}
	}
}

// ˢ�����з����ռ�����
void CYuApp::CheckBlock()
{	
	res = m_level;
	// ��ȫ����գ���ָ���ʾ�ǿյ�
	for (int i = 0; i < 13; ++i) for (int j = 0; j < 13; ++j) mp[i][j] = nullptr;
	m_Player.Check();
	m_FriendBox.Check();
	m_BoxHome.Check();
	m_StoneBox.Check();
}

void CYuApp::GameOver()
{
	::KillTimer(m_hWnd, CHECK_BLOCK_TIMEID);

	// ����Ͷ����Ϣ�����ڣ�Ȼ�󱻼�⵽���ûص����������˳�����
	PostMessage(m_hWnd, // ��˭������Ϣ
		WM_CLOSE, // ����ʲô��Ϣ
		NULL, NULL); // ��ϢЯ���Ĳ���
}

void CYuApp::NextStep()
{
	int x = m_StoneBox.m_StoneList.size();
	// ������һ��
	res = ++m_level;

	// ������һ�εĲо�
	m_FriendBox.Clear();
	m_BoxHome.Clear();
	m_TargetBox.Clear();
	m_StoneBox.Clear();

	int luck = ssr() % 100 + 1; // �����ж��ܷ�ˢ�����ѵ���������

	// �����һ�ص�Ŀ��ر��
	for (int i = 0; i < 13; ++i) for (int j = 0; j < 13; ++j) teg[i][j] = 0;

	// ��ʼ�����
	m_Player.InitPlayer(); // �����ﷵ�س�ʼλ��
	m_Player.InitFriend(); // ����ҵ�����������غ�

	// ��������
	if (!m_BoxHome.CreateBox(m_level)) {
		Win();
		return;
	}

	// ����Ұ������
	if (luck >= 70 + m_Player.m_FriendList.size() * 10) { // ����ӵ�е����ѱ�࣬ˢ�����ѵĸ��ʻ��С
		if (!m_FriendBox.CreateFriend(1)) {
			Win();
			return;
		}
	}

	// ����Ŀ�ĵ�
	m_TargetBox.CreateTarget(m_level);

	// ����ʯͷ
	if (!m_StoneBox.CreateStone(m_level * 2 + x)) {
		Win();
		return;
	}
}

void CYuApp::Win()
{
	::MessageBox(m_hWnd, L"��ϲͨ�أ�", L"��ʾ", MB_OK);
	GameOver();
}

void CYuApp::ReStart()
{
	// ���õ�ǰ�ؿ�
	res = m_level;

	int x = m_StoneBox.m_StoneList.size();

	// ������һ�εĲо�
	m_FriendBox.Clear();
	m_BoxHome.Clear();
	m_TargetBox.Clear();
	m_StoneBox.Clear();

	int luck = ssr() % 100 + 1; // �����ж��ܷ�ˢ�����ѵ���������

	// �����һ�ص�Ŀ��ر��
	for (int i = 0; i < 13; ++i) for (int j = 0; j < 13; ++j) teg[i][j] = 0;

	// ��ʼ�����
	m_Player.InitPlayer(); // �����ﷵ�س�ʼλ��
	m_Player.InitFriend(); // ����ҵ�����������غ�

	// ��������
	if (!m_BoxHome.CreateBox(m_level)) {
		Win();
		return;
	}

	// ����Ұ������
	if (luck >= 70 + m_Player.m_FriendList.size() * 10) { // ����ӵ�е����ѱ�࣬ˢ�����ѵĸ��ʻ��С
		if (!m_FriendBox.CreateFriend(1)) {
			Win();
			return;	
		}
	}

	// ����Ŀ�ĵ�
	m_TargetBox.CreateTarget(m_level);

	// ����ʯͷ
	if (!m_StoneBox.CreateStone(x)) {
		Win();
		return;
	}
}
