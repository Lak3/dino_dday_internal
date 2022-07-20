#pragma once

#include "../aimbot/aimbot.h"

class c_engine_prediction {
public:
	c_engine_prediction();
	~c_engine_prediction();

public:
	void start(c_user_cmd* cmd);
	void finish();

private:
	int get_tick_base(c_user_cmd* cmd);

private:
	float m_old_curtime   = 0.0f;
	float m_old_frametime = 0.0f;
	int m_old_tick_count  = 0;
	int m_old_flags       = 0;
	int m_old_tick_base   = 0;

	c_ddd_player* m_local = nullptr;

	c_move_data m_move_data = { };
};