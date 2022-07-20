#pragma once

#include "../features/features.h"

create_hook(calc_player_view, util.offsets->m_calc_player_view, void, __fastcall, c_base_player* ecx, void* edx, vector& eye_origin, vector& eye_angles, float& fov);
create_hook(cl_move, util.offsets->m_cl_move, void, __cdecl, float accumulated_extra_samples, bool final_tick);
create_hook(clientmode_createmove, util.offsets->m_clientmode_createmove, bool, __fastcall, void* ecx, void* edx, float input_sample_time, c_user_cmd* cmd);
create_hook(level_init_post_entity, util.vfunc->get<void*>(ints.base_client, 6u), void, __fastcall, void* ecx, void* edx);
create_hook(lock_cursor, util.vfunc->get<void*>(ints.surface, 65u), void, __fastcall, void* ecx, void* edx);
create_hook(on_screen_size_changed, util.vfunc->get<void*>(ints.surface, 114u), void, __fastcall, void* ecx, void* edx, int old_width, int old_height);
create_hook(paint, util.vfunc->get<void*>(ints.engine_vgui, 14u), void, __fastcall, void* ecx, void* edx, int mode);
create_hook(run_command, util.vfunc->get<void*>(ints.prediction, 19u), void, __fastcall, void* ecx, void* edx, c_base_player* plr, c_user_cmd* cmd, c_move_helper* helper);

class c_hooks {
public:
	bool initialize();
};

inline c_hooks hooks;































//not in sight not in existance
namespace hooked {
	namespace wndproc {
		inline WNDPROC wnd_proc = nullptr;
		inline HWND    window   = nullptr;

		long __stdcall func(HWND hwnd, unsigned int msg, unsigned int w_param, long l_param);

		bool initialize();
	}
}