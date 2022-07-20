#pragma once

#include "base_client.h"

//mactec
struct player_info_t {
public:
	int xuid_low;
	int xuid_high;
	char name[max_player_name_length];
	int userid;
	char guid[33];
	unsigned int steam3id;
	char friends_name[max_player_name_length];
	bool is_fake_player;
	bool is_hltv;
	unsigned long custom_files[max_custom_files];
	unsigned char files_downloaded;

private:
	unsigned char __pad00[4];
};

class c_engine_client {
public:
	__inline bool get_player_info(const int idx, player_info_t* pi) {
		return util.vfunc->get<bool(__thiscall*)(c_engine_client*, int, player_info_t*)>(this, 8u)(this, idx, pi);
	}

	__inline int get_local_player() {
		return util.vfunc->get<int(__thiscall*)(c_engine_client*)>(this, 12u)(this);
	}

	__inline void set_view_angles(vector& v) {
		util.vfunc->get<void(__thiscall*)(c_engine_client*, vector&)>(this, 19u)(this, v);
	}

	__inline int get_max_clients() {
		return util.vfunc->get<int(__thiscall*)(c_engine_client*)>(this, 20u)(this);
	}

	__inline bool is_in_game() {
		return util.vfunc->get<bool(__thiscall*)(c_engine_client*)>(this, 25u)(this);
	}

	__inline bool is_connected() {
		return util.vfunc->get<bool(__thiscall*)(c_engine_client*)>(this, 26u)(this);
	}

	__inline const matrix3x4_t& world_to_screen_matrix() {
		return util.vfunc->get<const matrix3x4_t& (__thiscall*)(c_engine_client*)>(this, 37u)(this);
	}

	__inline void client_cmd_unrestricted(const char* const cmd) {
		util.vfunc->get<void(__thiscall*)(c_engine_client*, const char*)>(this, 104u)(this, cmd);
	}
};