#pragma once

#include "move_helper.h"

class c_vgui_panel {
public:
	__inline const char* get_name(const int panel) {
		return util.vfunc->get<const char* (__thiscall*)(c_vgui_panel*, int)>(this, 36u)(this, panel);
	}
};