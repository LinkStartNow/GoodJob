#include "StoneBox.h"
#include "../Config/Config.h"

CStoneBox::CStoneBox() {}

CStoneBox::~CStoneBox()
{
	list<CStone*>::iterator it = m_StoneList.begin();
	while (it != m_StoneList.end()) {
		if (*it) {
			delete (*it);
			(*it) = nullptr;
		}
		++it;
	}
	m_StoneList.clear();
}

void CStoneBox::ShowAll()
{
	for (CStone* x : m_StoneList) {
		if (x) {
			x->ShowStone();
		}
	}
}

bool CStoneBox::CreateStone(int num)
{
	while (num) {
		if (Is_Full()) return false;
		int x = (int)(ssr() % 11) + 1; 
		int y = (int)(ssr() % 11) + 1;
		if (mp[x][y]) continue;
		CStone* p = new CStone;
		mp[x][y] = p;
		p->InitStone(x, y);
		m_StoneList.push_back(p);
		--num;
	}
	return true;
}

void CStoneBox::Check()
{
	for (CStone* x : m_StoneList) {
		if (x) {
			mp[x->m_x][x->m_y] = x;
		}
	}
}

void CStoneBox::Clear()
{
	list<CStone*>::iterator it = m_StoneList.begin();
	while (it != m_StoneList.end()) {
		if (*it) {
			delete (*it);
			(*it) = nullptr;
		}
		++it;
	}
	m_StoneList.clear();
}
