#pragma once

#include <random>

extern std::random_device ssr;

// ���е�ͼ����ĸ��ף��������
class CGod
{
public:
	int m_x;
	int m_y;

	virtual void yyds() {} // ֻ��Ϊ�˺��������ж����Ͱ���
};

extern CGod* mp[13][13];

extern bool teg[13][13];

extern int res;

bool Is_Full();

#define BLOCK_WIDTH 40

#define BACK_WIDTH 480

#define PLAYER_MOVE_STEP 1

// ��ʱ��
#define CHECK_BLOCK_TIMEID 1
#define CHECH_BLOCK_INTERVAL 100

// ����ռ��
#define PLAYER 1
#define FRIEND 2
#define BOX 3
