#include "Friend.h"
#include "../Config/Config.h"

CFriend::CFriend() : m_x(0), m_y(0) {}

CFriend::~CFriend() {}

void CFriend::InitFriend(int x, int y)
{
	m_x = x;
	m_y = y;

	::loadimage(&m_Friend, L"../res/Friend.jpg");
	::loadimage(&m_Mask, L"../res/Friend_Mask.jpg");
}

void CFriend::ShowFrined()
{
	putimage(m_x * BLOCK_WIDTH, m_y * BLOCK_WIDTH, &m_Mask, SRCPAINT);
	putimage(m_x * BLOCK_WIDTH, m_y * BLOCK_WIDTH, &m_Friend, SRCAND);
}