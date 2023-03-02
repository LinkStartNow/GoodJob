#include "BackGround.h"

CBackGround::CBackGround() : m_x(0), m_y(0) {}

CBackGround::~CBackGround() {}

void CBackGround::InitBack()
{
	::loadimage(&m_back, L"../res/GameBack.png");
}

void CBackGround::ShowBack()
{
	::putimage(m_x, m_y, &m_back);
}