#include "Target.h"
#include "../Config/Config.h"

CTarget::CTarget() : m_x(0), m_y(0) {}

CTarget::~CTarget() {}

void CTarget::InitTarget(int x, int y)
{
	m_x = x;
	m_y = y;

	::loadimage(&m_Target, L"../res/ssr.jpg");
}

void CTarget::ShowTarget()
{
	::putimage(m_x *BLOCK_WIDTH, m_y * BLOCK_WIDTH, &m_Target);
}