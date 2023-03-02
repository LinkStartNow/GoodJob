#pragma once

#include "Stone.h"

#include <list>

using namespace std;

class CStoneBox
{
public:
	list<CStone*> m_StoneList;

public:
	CStoneBox();
	~CStoneBox();
	void ShowAll();
	bool CreateStone(int num);
	void Check();
	void Clear();
};