#include "nospread.h"

c_nospread::c_nospread() {
	const auto hmod = GetModuleHandleW(L"vstdlib.dll");

	m_random_seed  = reinterpret_cast<fn_rseed>(GetProcAddress(hmod, "RandomSeed"));
	m_random_float = reinterpret_cast<fn_rfloat>(GetProcAddress(hmod, "RandomFloat"));
}

c_nospread::~c_nospread() {
	m_random_seed  = nullptr;
	m_random_float = nullptr;
}

void c_nospread::think(c_user_cmd* cmd) {
	if (!(cmd->buttons & in_attack))
		return;

	c_ddd_player* local_player = get_local();

	if (!local_player || local_player->get_deadflag())
		return;

	c_weapon_ddd_base* weapon = get_entity_from_handle(local_player->get_active_weapon())->as<c_weapon_ddd_base*>();

	if (!weapon)
		return;

	if (helpers.cvar->m_misc_nospread.get()) {
		m_random_seed((cmd->random_seed & 255) + 1); //+ 1???

		const float _x     = (m_random_float(-0.5f, 0.5f) + m_random_float(-0.5f, 0.5f));
		const float _y     = (m_random_float(-0.5f, 0.5f) + m_random_float(-0.5f, 0.5f));
		const float spread = weapon->get_spread();

		vector forward, right, up;
		util.math->angle_vectors(cmd->viewangles, &forward, &right, &up);

		vector new_angles = forward + (right * (_x * spread)) + (up * (_y * spread));
		new_angles.normalize();

		vector final_angle;
		util.math->vector_angles(new_angles, final_angle);
		final_angle = util.math->clamp_angles(final_angle);

		cmd->viewangles = util.math->clamp_angles((cmd->viewangles + (cmd->viewangles - final_angle)));
	}

	if (helpers.cvar->m_misc_norecoil.get())
		cmd->viewangles -= local_player->get_punch_angle();
}