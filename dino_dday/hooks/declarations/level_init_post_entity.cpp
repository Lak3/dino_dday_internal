#include "../hooks.h"

define_hook(level_init_post_entity, void, __fastcall, void* ecx, void* edx) {
	detour.original<fn>()(ecx, edx);

	features.esp->level_init_post_entity();
}