#include "YuApp.h"
#include "../Config/Config.h"

CREATE_OBJECT(CYuApp)
WINDOW_PARAM(520 + 16, 520 + 39, 40, 20, L"遇")

CYuApp::CYuApp() : m_level(0)
{

}

CYuApp::~CYuApp()
{

}

void CYuApp::Init()
{
	// 初始化第一关
	m_level = 1;

	// 初始化背景
	m_Back.InitBack();

	// 初始化玩家
	m_Player.InitPlayer();

	// 设定所有定时器
	SetTimer();

	// 创建箱子
	m_BoxHome.CreateBox(m_level);

	// 第一关就不造朋友了
	//// 生成野生朋友
	//m_FriendBox.CreateFriend(m_level);

	// 生成目的地
	m_TargetBox.CreateTarget(m_level);

	// 生成石头
	m_StoneBox.CreateStone(m_level * 2);
}

void CYuApp::Paint()
{
	// 显示背景
	m_Back.ShowBack();

	// 显示目的地
	m_TargetBox.ShowAll();

	// 显示玩家
	m_Player.ShowPlayer();

	// 显示玩家的朋友
	m_Player.ShowAllFriend();

	// 显示所有箱子
	m_BoxHome.ShowAll();

	// 显示所有野生朋友
	m_FriendBox.ShowAll();

	// 显示所有石头
	m_StoneBox.ShowAll();
}

void CYuApp::Close(WPARAM& w, LPARAM& l)
{

}

void CYuApp::ON_WM_KEYDOWN(WPARAM& key)
{
	static int help = 0;

	if (key == VK_UP || key == VK_DOWN || key == VK_LEFT || key == VK_RIGHT) { // 如果按方向键
		m_Player.MovePlayer(key, PLAYER_MOVE_STEP);
	}
	else if (key == 'F') { // 敲击了f键
		m_Player.GetFriend(m_FriendBox.Friending(m_Player));
	}
	else if (key == VK_SPACE) { // 敲击了空格
		::MessageBox(m_hWnd, L"你终于放弃啦！还是败给命运了吧！哈哈哈（无情嘲笑）", L"23333疯狂嘲笑", MB_OK);
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
		if (help == 3) { // 已经连续按下了 h e l
			if (m_Player.Is_Help) { // 已经使用过帮助，则不再帮助
				help = 0;
				::MessageBox(m_hWnd, L"你已经接受过一次帮助了，剩下的靠自己吧！", L"提示", MB_OK);
			}
			else { // 发出帮助，直接赐予非酋一个朋友
				m_Player.Is_Help = 1;
				CFriend* f = new CFriend;
				f->InitFriend(m_Player.m_x, m_Player.m_y);
				m_Player.m_FriendList.push_back(f);
			}
		}
	}
	// 聚集朋友
	else if (key == 'G') { 
		m_Player.InitFriend();
	}

	// 重置当前关卡
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
		if (!res) { // 箱子全部进入正确位置，进入下一关
			NextStep();
			::MessageBox(m_hWnd, L"恭喜！成功进入下一关！", L"提示", MB_OK);
			//GameOver();
			return;
		}
	}
	}
}

// 刷新所有方块的占有情况
void CYuApp::CheckBlock()
{	
	res = m_level;
	// 先全部清空，空指针表示是空地
	for (int i = 0; i < 13; ++i) for (int j = 0; j < 13; ++j) mp[i][j] = nullptr;
	m_Player.Check();
	m_FriendBox.Check();
	m_BoxHome.Check();
	m_StoneBox.Check();
}

void CYuApp::GameOver()
{
	::KillTimer(m_hWnd, CHECK_BLOCK_TIMEID);

	// 主动投递消息到窗口，然后被检测到利用回调函数处理退出动作
	PostMessage(m_hWnd, // 给谁发送消息
		WM_CLOSE, // 发送什么消息
		NULL, NULL); // 消息携带的参数
}

void CYuApp::NextStep()
{
	int x = m_StoneBox.m_StoneList.size();
	// 进入下一关
	res = ++m_level;

	// 清理上一次的残局
	m_FriendBox.Clear();
	m_BoxHome.Clear();
	m_TargetBox.Clear();
	m_StoneBox.Clear();

	int luck = ssr() % 100 + 1; // 用来判断能否刷出朋友的幸运数字

	// 清空上一关的目标地标记
	for (int i = 0; i < 13; ++i) for (int j = 0; j < 13; ++j) teg[i][j] = 0;

	// 初始化玩家
	m_Player.InitPlayer(); // 让人物返回初始位置
	m_Player.InitFriend(); // 让玩家的朋友与玩家重合

	// 创建箱子
	if (!m_BoxHome.CreateBox(m_level)) {
		Win();
		return;
	}

	// 生成野生朋友
	if (luck >= 70 + m_Player.m_FriendList.size() * 10) { // 随着拥有的朋友变多，刷出朋友的概率会变小
		if (!m_FriendBox.CreateFriend(1)) {
			Win();
			return;
		}
	}

	// 生成目的地
	m_TargetBox.CreateTarget(m_level);

	// 生成石头
	if (!m_StoneBox.CreateStone(m_level * 2 + x)) {
		Win();
		return;
	}
}

void CYuApp::Win()
{
	::MessageBox(m_hWnd, L"恭喜通关！", L"提示", MB_OK);
	GameOver();
}

void CYuApp::ReStart()
{
	// 重置当前关卡
	res = m_level;

	int x = m_StoneBox.m_StoneList.size();

	// 清理上一次的残局
	m_FriendBox.Clear();
	m_BoxHome.Clear();
	m_TargetBox.Clear();
	m_StoneBox.Clear();

	int luck = ssr() % 100 + 1; // 用来判断能否刷出朋友的幸运数字

	// 清空上一关的目标地标记
	for (int i = 0; i < 13; ++i) for (int j = 0; j < 13; ++j) teg[i][j] = 0;

	// 初始化玩家
	m_Player.InitPlayer(); // 让人物返回初始位置
	m_Player.InitFriend(); // 让玩家的朋友与玩家重合

	// 创建箱子
	if (!m_BoxHome.CreateBox(m_level)) {
		Win();
		return;
	}

	// 生成野生朋友
	if (luck >= 70 + m_Player.m_FriendList.size() * 10) { // 随着拥有的朋友变多，刷出朋友的概率会变小
		if (!m_FriendBox.CreateFriend(1)) {
			Win();
			return;	
		}
	}

	// 生成目的地
	m_TargetBox.CreateTarget(m_level);

	// 生成石头
	if (!m_StoneBox.CreateStone(x)) {
		Win();
		return;
	}
}
