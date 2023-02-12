#include "Player.h"
#include "../Config/Config.h"

CPlayer::CPlayer() : m_x(0), m_y(0) {}

CPlayer::~CPlayer()
{
	// 清空朋友列表
	list<CFriend*>::iterator it = m_FriendList.begin();
	while (it != m_FriendList.end()) {
		if ((*it)) {
			delete (*it);
			(*it) = nullptr;
		}
		++it;
	}
	m_FriendList.clear();
}

void CPlayer::InitPlayer()
{
	m_x = 0;
	m_y = 5;

	// 朋友测试
	//CFriend* p = new CFriend;
	//p->InitFriend(0, 0);
	//m_FriendList.push_back(p);

	//CFriend* p1 = new CFriend;
	//p1->InitFriend(0, 0);
	//m_FriendList.push_back(p1);

	//CFriend* p2 = new CFriend;
	//p2->InitFriend(0, 0);
	//m_FriendList.push_back(p2);

	//CFriend* p3 = new CFriend;
	//p3->InitFriend(0, 0);
	//m_FriendList.push_back(p3);

	::loadimage(&m_Player, L"../res/Boy.jpg");
	::loadimage(&m_Mask, L"../res/Boy_Mask.jpg");
}

void CPlayer::ShowPlayer()
{
	putimage(m_x * BLOCK_WIDTH, m_y * BLOCK_WIDTH, &m_Mask, SRCPAINT);
	putimage(m_x * BLOCK_WIDTH, m_y * BLOCK_WIDTH, &m_Player, SRCAND);
}

void CPlayer::MovePlayer(int direct, int step)
{
	int a = m_x, b = m_y;

// 宏替换带动朋友走的代码
#define MOVE_FRIEND()\
	if (m_FriendList.size()) {\
		list<CFriend*>::iterator it = --m_FriendList.end(); \
		if (m_FriendList.size() == 1) {\
				(*it)->m_x = m_x; \
				(*it)->m_y = m_y; \
		}\
		else {\
				list<CFriend*>::iterator its = it--; \
				while (it != m_FriendList.begin()) {\
						(*its)->m_x = (*it)->m_x; \
						(*its)->m_y = (*it)->m_y; \
						its = it--; \
				}\
			(*its)->m_x = (*it)->m_x; \
				(*its)->m_y = (*it)->m_y; \
				(*it)->m_x = m_x; \
				(*it)->m_y = m_y; \
		}\
	}

	if (direct == VK_UP) {
		if (m_y - step >= 0 && (!mp[a][b - 1])) {
			MOVE_FRIEND();
			m_y -= step;
		}
	}
	else if (direct == VK_DOWN) {
		if (m_y + step <= 12 && (!mp[a][b + 1])) {
			MOVE_FRIEND();
			m_y += step;
		}
	}
	else if (direct == VK_LEFT) {
		if (m_x - step >= 0 && (!mp[a - 1][b])) {
			MOVE_FRIEND();
			m_x -= step;
		}
	}
	else if (direct == VK_RIGHT) {
		if (m_x + step <= 12 && (!mp[a + 1][b])) {
			MOVE_FRIEND();
			m_x += step;
		}
	}
}

void CPlayer::ShowAllFriend()
{
	for (CFriend* x : m_FriendList) {
		if (x) {
			x->ShowFrined();
		}
	}
}

void CPlayer::Check()
{
	mp[m_x][m_y] = 1;
	for (CFriend* f : m_FriendList) {
		mp[f->m_x][f->m_y] = 1;
	}
}

void CPlayer::GetFriend(CFriend* f)
{
	if (!f) return;
	if (m_FriendList.size()) { // 之前已经有朋友了
		list<CFriend*>::iterator it = --m_FriendList.end();
		f->InitFriend((*it)->m_x, (*it)->m_y);
	}
	else {
		f->InitFriend(m_x, m_y);
	}
	m_FriendList.push_back(f);
}