#include "hooks.h"

bool c_hooks::initialize() {
	xassertf(mh_initialize() != mh_ok);
	{
		xassertf(hooked::calc_player_view::initialize() == failed_to_hook);
		xassertf(hooked::cl_move::initialize() == failed_to_hook);
		xassertf(hooked::clientmode_createmove::initialize() == failed_to_hook);
		xassertf(hooked::level_init_post_entity::initialize() == failed_to_hook);
		xassertf(hooked::lock_cursor::initialize() == failed_to_hook);
		xassertf(hooked::on_screen_size_changed::initialize() == failed_to_hook);
		xassertf(hooked::paint::initialize() == failed_to_hook);
		xassertf(hooked::run_command::initialize() == failed_to_hook);
		xassertf(hooked::wndproc::initialize() == failed_to_hook);
	}
	xassertf(mh_enablehook(mh_all_hooks) != mh_ok);

	console_msg("c_hooks::initialize() finished successfully.\n");
	return true;
}