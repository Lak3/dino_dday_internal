#include "../hooks.h"

define_hook(clientmode_createmove, bool, __fastcall, void* ecx, void* edx, float input_sample_time, c_user_cmd* cmd) {
	if (!cmd || !cmd->command_number)
		return detour.original<fn>()(ecx, edx, input_sample_time, cmd);

	features.misc->think(cmd);

	features.engine_prediction->start(cmd); {
		features.aimbot->think(cmd);
		features.nospread->think(cmd);
	}
	features.engine_prediction->finish();

	return false;
}