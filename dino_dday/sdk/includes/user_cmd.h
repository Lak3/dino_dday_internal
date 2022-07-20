#pragma once

#include "client_class.h"

//mactec
class c_user_cmd {
private:
	char    __pad00[4];

public:
	int	    command_number;
	int     tick_count;
	vector  viewangles;
	float   forwardmove;
	float   sidemove;
	float   upmove;
	int     buttons;

private:
	char    __pad01[12];

public:
	int     random_seed;
	short	mousedx;
	short	mousedy;
	bool    hasbeenpredicted;

private:
	char    __pad02[27];
};

class c_verified_user_cmd {
public:
	c_user_cmd m_cmd;
	crc32_t    m_crc; 
};