#include "Box .h"

CBox::CBox() { m_x = m_y = 0; }

CBox::~CBox() {}

void CBox::InitBox(int x, int y)
{
	m_x = x;
	m_y = y;
	::loadimage(&m_Box, L"../res/box.jpg");
	::loadimage(&m_BoxYes, L"../res/yes.jpg");
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

void CBox::ShowBox()
{
	if (teg[m_x][m_y]) { // 如果推到了目标位置
		SHOW(m_BoxYes);
	}
	else {
		SHOW(m_Box);
	}

	//// 先显示屏蔽图
	//::putimage(m_x * BLOCK_WIDTH, m_y * BLOCK_WIDTH, // 这是在窗口的坐标
	//	BLOCK_WIDTH, BLOCK_WIDTH, // 显示的宽高
	//	&m_Box, // 图片
	//	BLOCK_WIDTH, 0, // 从源图的哪个位置显示
	//	SRCPAINT);

	//// 再显示原图
	//::putimage(m_x * BLOCK_WIDTH, m_y * BLOCK_WIDTH, // 这是在窗口的坐标
	//	BLOCK_WIDTH, BLOCK_WIDTH, // 显示的宽高
	//	&m_Box, // 图片
	//	0, 0, // 从源图的哪个位置显示
	//	SRCAND);
}

#undef SHOW
