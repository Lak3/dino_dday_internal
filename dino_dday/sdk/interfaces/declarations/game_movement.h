#pragma once

#include "entity_list.h"

class c_base_player;

class c_move_data {
private:
	char __pad00[168];
};

class c_game_movement {
public:
	__inline void process_movement(c_base_player* plr, void* move) {
		util.vfunc->get<void(__thiscall*)(c_game_movement*, c_base_player*, void*)>(this, 1u)(this, plr, move);
	}
};