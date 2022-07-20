#include "../hooks.h"

define_hook(paint, void, __fastcall, void* ecx, void* edx, int mode) {
	detour.original<fn>()(ecx, edx, mode);

	if (!(mode & paint_uipanels))
		return;

	helpers.input->think();

	ints.surface->start_drawing();
	{
		helpers.draw->string(font_debug, 5, 5, color_white, txt_default, L"Dino D-Day internal by Lak3 - unknowncheats.me");

		features.esp->think();
		features.menu->think();

		if (helpers.input->is_pressed(46)) //del
			ints.engine_client->client_cmd_unrestricted("toggleconsole");
	}
	ints.surface->finish_drawing();
}