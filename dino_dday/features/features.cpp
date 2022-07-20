#include "features.h"

c_features::c_features() {
	aimbot            = std::make_unique<c_aimbot>();
	engine_prediction = std::make_unique<c_engine_prediction>();
	esp               = std::make_unique<c_esp>();
	menu              = std::make_unique<c_menu>();
	misc              = std::make_unique<c_misc>();
	nospread          = std::make_unique<c_nospread>();

	console_msg("c_features::c_features() initialized feature pointers.\n");
}

c_features::~c_features() {
	aimbot.reset();
	engine_prediction.reset();
	esp.reset();
	menu.release();
	misc.reset();
	nospread.reset();
}