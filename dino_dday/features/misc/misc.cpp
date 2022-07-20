#include "misc.h"

void c_misc::think(c_user_cmd* cmd) {
	if (!ints.engine_client->is_connected() || !ints.engine_client->is_in_game())
		return;

	null_setinfo();

	c_ddd_player* local_player = get_local();

	if (!local_player || local_player->get_deadflag())
		return;

	bunny_hop(local_player, cmd);
}

void c_misc::bunny_hop(c_ddd_player* local_player, c_user_cmd* cmd) {
	if (helpers.cvar->m_misc_bhop.get() && (cmd->buttons & in_jump) && !(local_player->get_flags() & fl_onground))
		cmd->buttons &= ~in_jump;
}

void c_misc::null_setinfo() {
	if (!helpers.cvar->m_misc_setinfo_null.get())
		return;

	ints.engine_client->client_cmd_unrestricted("setinfo name \"\"");

	helpers.cvar->m_misc_setinfo_null.set(false);
}