#pragma once

#include "engine_trace.h"

#define paint_uipanels (1 << 0)
#define paint_in_game_panels (1 << 1)

class c_engine_vgui {
public:
	__inline bool is_game_ui_visible() {
		return util.vfunc->get<bool(__thiscall*)(c_engine_vgui*)>(this, 2u)(this);
	}
};