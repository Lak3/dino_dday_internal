#pragma once

#include "../../includes/includes.h"

class c_base_client {
public:
	__inline client_class* get_all_classes() {
		return util.vfunc->get<client_class* (__thiscall*)(c_base_client*)>(this, 8u)(this);
	}

	__inline int get_screen_width() {
		return util.vfunc->get<int(__thiscall*)(c_base_client*)>(this, 60u)(this);
	}

	__inline int get_screen_height() {
		return util.vfunc->get<int(__thiscall*)(c_base_client*)>(this, 61u)(this);
	}
};