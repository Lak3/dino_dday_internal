#include "offsets.h"
#include "../util.h"

#define failed_to_find_pattern 0u

c_offsets::c_offsets() {
	m_start_drawing         = 0u;
	m_finish_drawing        = 0u;
	m_cl_move               = 0u;
	m_clientmode_createmove = 0u;
	m_set_pred_rand_seed    = 0u;
	m_instance              = 0u;
	m_update_button_state   = 0u;
	m_calc_player_view      = 0u;
}

c_offsets::~c_offsets() {
	m_start_drawing         = 0u;
	m_finish_drawing        = 0u;
	m_cl_move               = 0u;
	m_clientmode_createmove = 0u;
	m_set_pred_rand_seed    = 0u;
	m_instance              = 0u;
	m_update_button_state   = 0u;
	m_calc_player_view      = 0u;
}

bool c_offsets::initialize() {
	m_start_drawing = util.pattern->find("vguimatsurface.dll", "55 8B EC 83 EC 10 80 3D ? ? ? ? ? 56 57 8B F9 75 57");
	xassertf(m_start_drawing == failed_to_find_pattern);

	m_finish_drawing = util.pattern->find("vguimatsurface.dll", "56 6A 00 E8 ? ? ? ? 8B 0D ? ? ? ? 8B 01");
	xassertf(m_finish_drawing == failed_to_find_pattern);

	m_cl_move = util.pattern->find("engine.dll", "55 8B EC 83 EC 24 56");
	xassertf(m_cl_move == failed_to_find_pattern);

	m_clientmode_createmove = util.pattern->find("client.dll", "55 8B EC 6A FF E8 ? ? ? ? 83 C4 04 85 C0 75 06 B0 01 5D");
	xassertf(m_clientmode_createmove == failed_to_find_pattern);

	m_set_pred_rand_seed = util.pattern->find("client.dll", "55 8B EC 8B 45 08 85 C0 75 0C");
	xassertf(m_set_pred_rand_seed == failed_to_find_pattern);

	m_instance = util.pattern->find("client.dll", "55 8B EC 8B 45 08 8B 0D ? ? ? ? 50 E8 ? ? ? ? 5D C3");
	xassertf(m_instance == failed_to_find_pattern);

	m_update_button_state = util.pattern->find("client.dll", "55 8B EC 8B 81 ? ? ? ? 89 81 ? ? ? ?");
	xassertf(m_update_button_state == failed_to_find_pattern);

	m_calc_player_view = util.pattern->find("client.dll", "55 8B EC 83 EC 1C 53 56 8B F1 8B 0D ? ? ? ?");
	xassertf(m_calc_player_view == failed_to_find_pattern);

	console_msg("c_offsets::initialize() finished successfully.\n");
	return true;
}