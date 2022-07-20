#pragma once

#include "panel.h"

class c_move_helper;

class c_prediction {
public:
	__inline void set_local_view_angles(vector& v) {
		util.vfunc->get<void(__thiscall*)(c_prediction*, vector&)>(this, 13u)(this, v);
	}

	__inline void run_command(c_base_player* plr, c_user_cmd* cmd, c_move_helper* helper) {
		util.vfunc->get<void(__thiscall*)(c_prediction*, c_base_player*, c_user_cmd*, c_move_helper*)>(this, 19u)(this, plr, cmd, helper);
	}

	__inline void setup_move(c_base_player* plr, c_user_cmd* cmd, c_move_helper* helper, void* move) {
		util.vfunc->get<void(__thiscall*)(c_prediction*, c_base_player*, c_user_cmd*, c_move_helper*, void*)>(this, 20u)(this, plr, cmd, helper, move);
	}

	__inline void finish_move(c_base_player* plr, c_user_cmd* cmd, void* move) {
		util.vfunc->get<void(__thiscall*)(c_prediction*, c_base_player*, c_user_cmd*, void*)>(this, 21u)(this, plr, cmd, move);
	}
};