#pragma once

#include <random>

extern std::random_device ssr;

// 所有地图上类的父亲，用来配合
class CGod
{
public:
	int m_x;
	int m_y;

	virtual void yyds() {} // 只是为了后续方便判断类型罢了
};

extern CGod* mp[13][13];

extern bool teg[13][13];

extern int res;

bool Is_Full();

#define BLOCK_WIDTH 40

#define BACK_WIDTH 480

#define PLAYER_MOVE_STEP 1

// 定时器
#define CHECK_BLOCK_TIMEID 1
#define CHECH_BLOCK_INTERVAL 100

// 方格占用
#define PLAYER 1
#define FRIEND 2
#define BOX 3
