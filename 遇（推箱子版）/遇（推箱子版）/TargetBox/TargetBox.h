#pragma once

#include "Target.h"

#include <list>

using namespace std;

class CTargetBox
{
public:
	list<CTarget*> m_TargetList;

public:
	CTargetBox();
	~CTargetBox();
	void ShowAll();
	void CreateTarget(int num);
	void Clear();
};