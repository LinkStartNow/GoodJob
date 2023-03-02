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
	if (teg[m_x][m_y]) { // ����Ƶ���Ŀ��λ��
		SHOW(m_BoxYes);
	}
	else {
		SHOW(m_Box);
	}

	//// ����ʾ����ͼ
	//::putimage(m_x * BLOCK_WIDTH, m_y * BLOCK_WIDTH, // �����ڴ��ڵ�����
	//	BLOCK_WIDTH, BLOCK_WIDTH, // ��ʾ�Ŀ��
	//	&m_Box, // ͼƬ
	//	BLOCK_WIDTH, 0, // ��Դͼ���ĸ�λ����ʾ
	//	SRCPAINT);

	//// ����ʾԭͼ
	//::putimage(m_x * BLOCK_WIDTH, m_y * BLOCK_WIDTH, // �����ڴ��ڵ�����
	//	BLOCK_WIDTH, BLOCK_WIDTH, // ��ʾ�Ŀ��
	//	&m_Box, // ͼƬ
	//	0, 0, // ��Դͼ���ĸ�λ����ʾ
	//	SRCAND);
}

#undef SHOW
