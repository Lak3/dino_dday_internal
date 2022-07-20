#include "../hooks.h"

define_hook(run_command, void, __fastcall, void* ecx, void* edx, c_base_player* plr, c_user_cmd* cmd, c_move_helper* helper) {
	detour.original<fn>()(ecx, edx, plr, cmd, helper);

	if (!ints.move_helper && helper)
		ints.move_helper = helper;
}