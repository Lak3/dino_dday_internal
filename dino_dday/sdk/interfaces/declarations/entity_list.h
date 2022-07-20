#pragma once

#include "engine_vgui.h"

class c_client_entity;

class c_client_entity_list {
public:
	__inline c_client_entity* get_client_entity(const int idx) {
		return util.vfunc->get<c_client_entity* (__thiscall*)(c_client_entity_list*, int)>(this, 3u)(this, idx);
	}

	__inline c_client_entity* get_client_entity_from_handle(c_base_handle hent /* ai? */) {
		return util.vfunc->get<c_client_entity* (__thiscall*)(c_client_entity_list*, c_base_handle)>(this, 4u)(this, hent);
	}

	__inline int get_highest_entity_index() {
		return util.vfunc->get<int(__thiscall*)(c_client_entity_list*)>(this, 6u)(this);
	}
};