#include "Player.h"
#include "../Config/Config.h"
#include "../FriendBox/Friend.h"
#include "../BoxHome/Box .h"
#include "../StoneBox/Stone.h"

#include <typeinfo>

//bool Check_IsFriend(int x, int y)
//{
//	if (!mp[x][y]) return false;
//	if (typeid(*(mp[x][y])) == typeid(CFriend)) {
//		return true;
//	}
//	return false;
//}
//
//bool Check_IsBox(int x, int y)
//{
//	if (!mp[x][y]) return false;
//	if (typeid(*(mp[x][y])) == typeid(CBox)) {
//		return true;
//	}
//	return false;
//}
//
//bool Check_IsStone(int x, int y)
//{
//	if (!mp[x][y]) return false;
//	if (typeid(*(mp[x][y])) == typeid(CStone)) {
//		return true;
//	}
//	return false;
//}

template <typename T>
bool Check_IsWhat(int x, int y)
{
	if (!mp[x][y]) return false;
	if (typeid(*(mp[x][y])) == typeid(T)) {
		return true;
	}
	return false;
}

CPlayer::CPlayer() : Is_Help(false) { m_x = m_y = 0; }

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

	mp[m_x][m_y] = this;

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

bool Push(int direct, int step, int x, int y, CPlayer* player)
{
	// 0 1 2 3代表上下左右
	int sx = x, sy = y;
	bool flag = false;
	switch (direct) {

	// 上
	case 0:
		while (sy >= 0 && mp[sx][sy]) { // 试图去寻找一块空地
			if (Check_IsWhat<CFriend>(sx, sy)) return false; // 如果碰到朋友了默认不能推
			--sy;
		}
		if (sy >= 0) flag = true; // 成功找到空地
		if (y - sy > player->m_FriendList.size() + 1) flag = false;
		if (!flag) return false;
		for (int i = y; i > sy; --i) { // 沿途的箱子全部移动
			mp[x][i]->m_y -= step;
		}
		break;

	// 下
	case 1:
		while (sy <= 12 && mp[sx][sy]) { // 试图去寻找一块空地
			if (Check_IsWhat<CFriend>(sx, sy)) return false; // 如果碰到朋友了默认不能推
			++sy;
		}
		if (sy <= 12) flag = true; // 成功找到空地
		if (sy - y > player->m_FriendList.size() + 1) flag = false;
		if (!flag) return false;
		for (int i = y; i < sy; ++i) { // 沿途的箱子全部移动
			mp[x][i]->m_y += step;
		}
		break;

	// 左
	case 2:
		while (sx >= 0 && mp[sx][sy]) { // 试图去寻找一块空地
			if (Check_IsWhat<CFriend>(sx, sy)) return false; // 如果碰到朋友了默认不能推
			--sx;
		}
		if (sx >= 0) flag = true; // 成功找到空地
		if (x - sx > player->m_FriendList.size() + 1) flag = false;
		if (!flag) return false;
		for (int i = x; i > sx; --i) { // 沿途的箱子全部移动
			mp[i][y]->m_x -= step;
		}
		break;

	// 右
	case 3:
		while (sx <= 12 && mp[sx][sy]) { // 试图去寻找一块空地
			if (Check_IsWhat<CFriend>(sx, sy)) return false; // 如果碰到朋友了默认不能推
			++sx;
		}
		if (sx <= 12) flag = true; // 成功找到空地
		if (sx - x > player->m_FriendList.size() + 1) flag = false;
		if (!flag) return false;
		for (int i = x; i < sx; ++i) { // 沿途的箱子全部移动
			mp[i][y]->m_x += step;
		}
		break;
	}

	return true;
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
		if (m_y - step >= 0) {
			if (Check_IsWhat<CFriend>(m_x, m_y - step) || Check_IsWhat<CStone>(m_x, m_y - step)) return; // 不能推朋友
			if (Check_IsWhat<CBox>(m_x, m_y - step)) { // 如果是箱子，判断能不能推
				if (!Push(0, step, m_x, m_y - step, this)) return; // 如果不能推，则直接退出
			}
			MOVE_FRIEND();
			m_y -= step;
		}
	}
	else if (direct == VK_DOWN) {
		if (m_y + step <= 12) {
			if (Check_IsWhat<CFriend>(m_x, m_y + step) || Check_IsWhat<CStone>(m_x, m_y + step)) return; // 不能推朋友
			if (Check_IsWhat<CBox>(m_x, m_y + step)) { // 如果是箱子，判断能不能推
				if (!Push(1, step, m_x, m_y + step, this)) return; // 如果不能推，则直接退出
			}
			MOVE_FRIEND();
			m_y += step;
		}
	}
	else if (direct == VK_LEFT) {
		if (m_x - step >= 0) {
			if (Check_IsWhat<CFriend>(m_x - step, m_y) || Check_IsWhat<CStone>(m_x - step, m_y)) return; // 不能推朋友
			if (Check_IsWhat<CBox>(m_x - step, m_y)) { // 如果是箱子，判断能不能推
				if (!Push(2, step, m_x - step, m_y, this)) return; // 如果不能推，则直接退出
			}
			MOVE_FRIEND();
			m_x -= step;
		}
	}
	else if (direct == VK_RIGHT) {
		if (m_x + step <= 12) {
			if (Check_IsWhat<CFriend>(m_x + step, m_y) || Check_IsWhat<CStone>(m_x + step, m_y)) return; // 不能推朋友
			if (Check_IsWhat<CBox>(m_x + step, m_y)) { // 如果是箱子，判断能不能推
				if (!Push(3, step, m_x + step, m_y, this)) return; // 如果不能推，则直接退出
			}
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
	mp[m_x][m_y] = this;
	for (CFriend* f : m_FriendList) {
		mp[f->m_x][f->m_y] = f;
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

void CPlayer::InitFriend()
{
	for (CFriend*& f : m_FriendList) {
		if (f) {
			f->m_x = m_x;
			f->m_y = m_y;
		}
	}
}
