#include "../hooks.h"

define_hook(lock_cursor, void, __fastcall, void* ecx, void* edx) {
	if (features.menu->is_open())
		ints.surface->unlock_cursor();
	else
		detour.original<fn>()(ecx, edx);
}