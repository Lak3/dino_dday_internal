#pragma once

#include "../vfunc/vfunc.h"

class c_offsets {
public:
	c_offsets();
	~c_offsets();

public:
	bool initialize();

public:
	unsigned long m_start_drawing         = 0u;
	unsigned long m_finish_drawing        = 0u;
	unsigned long m_cl_move               = 0u;
	unsigned long m_clientmode_createmove = 0u;
	unsigned long m_set_pred_rand_seed    = 0u;
	unsigned long m_instance              = 0u;
	unsigned long m_update_button_state   = 0u;
	unsigned long m_calc_player_view      = 0u;
};