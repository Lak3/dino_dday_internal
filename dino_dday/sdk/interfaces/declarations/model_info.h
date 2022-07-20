#pragma once

#include "game_movement.h"

struct model_t;

class c_model_info_client {
public:
	__inline model_t* get_model(const int idx) {
		return util.vfunc->get<model_t* (__thiscall*)(c_model_info_client*, int)>(this, 1u)(this, idx);
	}

	__inline int get_model_index(const char* const path) {
		return util.vfunc->get<int(__thiscall*)(c_model_info_client*, const char*)>(this, 2u)(this, path);
	}

	__inline const char* get_model_name(const model_t* mdl) {
		return util.vfunc->get<const char* (__thiscall*)(c_model_info_client*, const model_t*)>(this, 3u)(this, mdl);
	}

	__inline studiohdr_t* get_studio_model(const model_t* mdl) {
		return util.vfunc->get<studiohdr_t* (__thiscall*)(c_model_info_client*, const model_t*)>(this, 30u)(this, mdl);
	}
};