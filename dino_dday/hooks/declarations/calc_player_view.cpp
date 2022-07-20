#include "../hooks.h"

define_hook(calc_player_view, void, __fastcall, c_base_player* ecx, void* edx, vector& eye_origin, vector& eye_angles, float& fov) {
	if (helpers.cvar->m_misc_novis_recoil.get() && ecx && (ecx->entindex() == ints.engine_client->get_local_player())) {
		const vector old_punch = ecx->get_punch_angle();

		ecx->set_punch_angle({ 0.0f, 0.0f, 0.0f });
		detour.original<fn>()(ecx, edx, eye_origin, eye_angles, fov);
		ecx->set_punch_angle(old_punch);
	}
	else {
		detour.original<fn>()(ecx, edx, eye_origin, eye_angles, fov);
	}
}