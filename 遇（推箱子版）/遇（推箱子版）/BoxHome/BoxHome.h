#pragma once

#include "Box .h"

#include <list>

using namespace std;

class CBoxHome
{
public:
	list<CBox*> m_BoxList;

public:
	CBoxHome();
	~CBoxHome();
	void ShowAll();
	bool CreateBox(int num);
	void Check();
	void Clear();
};