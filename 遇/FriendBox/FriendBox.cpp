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

void CFriendBox::CreateFriend(int num)
{
	while (num) {
		int x = ssr() % 13;
		int y = ssr() % 13;
		if (mp[x][y]) continue;
		mp[x][y] = 1;
		CFriend* p = new CFriend;
		p->InitFriend(x, y);
		m_FriendBoxList.push_back(p);
		--num;
	}
}

void CFriendBox::Check()
{
	for (CFriend* x : m_FriendBoxList) {
		if (x) {
			mp[x->m_x][x->m_y] = 1;
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