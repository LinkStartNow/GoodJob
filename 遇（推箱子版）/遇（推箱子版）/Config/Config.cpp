#include "Config.h"

std::random_device ssr;

CGod* mp[13][13] = { nullptr };

bool teg[13][13] = { 0 };

int res = 3;

bool Is_Full()
{
	for (int i = 1; i < 12; ++i) for (int j = 1; j < 12; ++j) if (!mp[i][j]) return false;
	return true;
}