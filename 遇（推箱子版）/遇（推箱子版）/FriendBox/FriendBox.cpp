#include "FriendBox.h"
#include "../Config/Config.h"

CFriendBox::CFriendBox() {}

CFriendBox::~CFriendBox()
{
	list<CFriend*>::iterator it = m_FriendBoxList.begin();
	while (it != m_FriendBoxList.end()) {
		if ((*it)) {
			delete (*it);
			(*it) = nullptr;
		}
		++it;
	}
	m_FriendBoxList.clear();
}

void CFriendBox::ShowAll()
{
	for (CFriend* x : m_FriendBoxList) {
		if (x) {
			x->ShowFrined();
		}
	}
}

bool CFriendBox::CreateFriend(int num)
{
	while (num) {
		if (Is_Full()) return false;
		int x = ssr() % 13;
		int y = ssr() % 13;
		if (mp[x][y]) continue;
		CFriend* p = new CFriend;
		mp[x][y] = p;
		p->InitFriend(x, y);
		m_FriendBoxList.push_back(p);
		--num;
	}
	return true;
}

void CFriendBox::Check()
{
	for (CFriend* x : m_FriendBoxList) {
		if (x) {
			mp[x->m_x][x->m_y] = x;
		}
	}
}

CFriend* CFriendBox::Friending(CPlayer& player)
{
	CFriend* res = nullptr;
	list<CFriend*>::iterator it = m_FriendBoxList.begin();
	while (it != m_FriendBoxList.end()) {
		if (*it) { // 节点存在
			if ((abs((*it)->m_x - player.m_x) + abs((*it)->m_y - player.m_y)) == 1) { // 距离只有一格
				res = (*it);
				m_FriendBoxList.erase(it);
				return res;
			}
		}
		++it;
	}
	return res;
}

void CFriendBox::Clear()
{
	list<CFriend*>::iterator it = m_FriendBoxList.begin();
	while (it != m_FriendBoxList.end()) {
		if ((*it)) {
			delete (*it);
			(*it) = nullptr;
		}
		++it;
	}
	m_FriendBoxList.clear();
}
