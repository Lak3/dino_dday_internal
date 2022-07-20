#include "../hooks.h"

#define failed_while_screen_size_changed false

define_hook(on_screen_size_changed, void, __fastcall, void* ecx, void* edx, int old_width, int old_height) {
	detour.original<fn>()(ecx, edx, old_width, old_height);

	xassert(helpers.draw->initialize() == failed_while_screen_size_changed);
}