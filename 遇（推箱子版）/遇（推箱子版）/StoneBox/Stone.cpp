#include "Stone.h"

CStone::CStone() { m_x = m_y = 0; }

CStone::~CStone() {}

void CStone::InitStone(int x, int y)
{
	m_x = x;
	m_y = y;
	::loadimage(&m_Stone, L"../res/stone.jpg");
}

#define SHOW(BOX)\
::putimage(m_x* BLOCK_WIDTH, m_y* BLOCK_WIDTH, \
	BLOCK_WIDTH, BLOCK_WIDTH, \
	&BOX, \
	BLOCK_WIDTH, 0, \
	SRCPAINT);\
::putimage(m_x* BLOCK_WIDTH, m_y* BLOCK_WIDTH, \
	BLOCK_WIDTH, BLOCK_WIDTH, \
	&BOX, \
	0, 0, \
	SRCAND);

void CStone::ShowStone()
{
	SHOW(m_Stone);
}

#undef SHOW
