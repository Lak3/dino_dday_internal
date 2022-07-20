#pragma once

#include "../menu/menu.h"

class c_misc {
public:
	void think(c_user_cmd* cmd);

private:
	void bunny_hop(c_ddd_player* local_player, c_user_cmd* cmd);
	void null_setinfo();
};