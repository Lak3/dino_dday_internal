#pragma once

#include "user_cmd.h"

class c_globalvars_base {
public:
	float			realtime;
	int				framecount;
	float			absoluteframetime;
	float			curtime;
	float			frametime;
	int				max_clients;
	int				tickcount;
	float			interval_per_tick;
	float			interpolation_amount;
	int				sim_ticks_this_frame;
	int				network_protocol;
	void*           save_data;
	bool			is_client;
	int				time_stamp_networking_base;
	int				time_stamp_randomize_window;
};