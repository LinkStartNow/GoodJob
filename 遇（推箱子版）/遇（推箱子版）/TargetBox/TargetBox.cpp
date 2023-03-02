#include "TargetBox.h"
#include "../Config/Config.h"

CTargetBox::CTargetBox() {}

CTargetBox::~CTargetBox()
{
	list<CTarget*>::iterator it = m_TargetList.begin();
	while (it != m_TargetList.end()) {
		if (*it) {
			delete (*it);
			(*it) = nullptr;
		}
		++it;
	}
	m_TargetList.clear();
}

void CTargetBox::ShowAll()
{
	for (CTarget* x : m_TargetList) {
		if (x) {
			x->ShowTarget();
		}
	}
}
void CTargetBox::CreateTarget(int num)
{
	while (num) {
		int x = ssr() % 13; 
		int y = ssr() % 13;
		if (teg[x][y]) continue;
		teg[x][y] = 1;
		CTarget* p = new CTarget;
		p->InitTarget(x, y);
		m_TargetList.push_back(p);
		--num;
	}
}

void CTargetBox::Clear()
{
	list<CTarget*>::iterator it = m_TargetList.begin();
	while (it != m_TargetList.end()) {
		if (*it) {
			delete (*it);
			(*it) = nullptr;
		}
		++it;
	}
	m_TargetList.clear();
}
