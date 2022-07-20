#pragma once

#include "../misc/misc.h"

class c_nospread {
public:
	c_nospread();
	~c_nospread();

public:
	void think(c_user_cmd* cmd);

private:
	using fn_rseed  = void(__cdecl*)(int);
	using fn_rfloat = float(__cdecl*)(float, float);

private:
	fn_rseed  m_random_seed  = nullptr;
	fn_rfloat m_random_float = nullptr;
};