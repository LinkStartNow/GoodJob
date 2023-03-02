#include "BoxHome.h"
#include "../Config/Config.h"

CBoxHome::CBoxHome() {}

CBoxHome::~CBoxHome()
{
	list<CBox*>::iterator it = m_BoxList.begin();
	while (it != m_BoxList.end()) {
		if (*it) {
			delete (*it);
			(*it) = nullptr;
		}
		++it;
	}
	m_BoxList.clear();
}

void CBoxHome::ShowAll()
{
	for (CBox* x : m_BoxList) {
		if (x) {
			x->ShowBox();
		}
	}
}

bool CBoxHome::CreateBox(int num)
{
	while (num) {
		if (Is_Full()) return false;
		int x = (int)(ssr() % 11) + 1; // ������ӳ�ʼ���ڵײ�����ô��Ϸ����ͻ᲻��
		int y = (int)(ssr() % 11) + 1;
		if (mp[x][y]) continue;
		CBox* p = new CBox;
		mp[x][y] = p;
		p->InitBox(x, y);
		m_BoxList.push_back(p);
		--num;
	}
	return true;
}

void CBoxHome::Check()
{
	for (CBox* x : m_BoxList) {
		if (x) {
			mp[x->m_x][x->m_y] = x;
			if (teg[x->m_x][x->m_y]) --res; // ������ָ��λ�ã���ʣ��Ŀ���һ
		}
	}
}

void CBoxHome::Clear()
{
	list<CBox*>::iterator it = m_BoxList.begin();
	while (it != m_BoxList.end()) {
		if (*it) {
			delete (*it);
			(*it) = nullptr;
		}
		++it;
	}
	m_BoxList.clear();
}
