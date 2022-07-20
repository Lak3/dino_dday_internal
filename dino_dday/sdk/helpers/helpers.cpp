#include "helpers.h"

c_helpers::c_helpers() {
	cvar   = std::make_unique<c_control_variables>();
	draw   = std::make_unique<c_draw_manager>();
	input  = std::make_unique<c_input>();
	netvar = std::make_unique<c_netvar_manager>();

	console_msg("c_helpers::c_helpers() initialized helper pointers.\n");
}

c_helpers::~c_helpers() {
	cvar.release();
	draw.reset();
	input.reset();
	netvar.reset();
}